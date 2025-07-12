#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <ArduinoJson.h>
#include <NimBLEDevice.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int cpu = 0, ram = 0, disk = 0, net = 0;
String jsonStr = "";
volatile bool bleConnected = false;

// BLE Server Callbacks for connection state
class MyServerCallbacks : public NimBLEServerCallbacks {
  void onConnect(NimBLEServer* pServer, NimBLEConnInfo& connInfo) override {
    bleConnected = true;
    Serial.println("BLE client connected (server callback)");
  }
  void onDisconnect(NimBLEServer* pServer, NimBLEConnInfo& connInfo, int reason) override {
    bleConnected = false;
    Serial.println("BLE client disconnected (server callback)");
    NimBLEAdvertising* pAdvertising = NimBLEDevice::getAdvertising();
    pAdvertising->start();
    Serial.println("BLE advertising restarted");
  }
};

// BLE UUIDs (same as Python)
#define SERVICE_UUID        "12345678-1234-1234-1234-123456789abc"
#define CHARACTERISTIC_UUID "abcdefab-1234-1234-1234-abcdefabcdef"

// === BLE Write Callback Handler ===
class StatsCallbacks : public NimBLECharacteristicCallbacks {
  void onWrite(NimBLECharacteristic* pCharacteristic, NimBLEConnInfo& connInfo) override {
    Serial.println("⚡ BLE Write Callback Triggered");

    std::string value = pCharacteristic->getValue();
    for (char c : value) {
      if (c == '\n') {
        StaticJsonDocument<200> doc;
        DeserializationError error = deserializeJson(doc, jsonStr);
        if (!error) {
          cpu = doc["cpu"];
          ram = doc["ram"];
          disk = doc["hdd"];
          net = doc["net"];
          Serial.printf("Parsed: CPU=%d RAM=%d DISK=%d NET=%d\n", cpu, ram, disk, net);
        } else {
          Serial.println("❌ JSON Parse Error");
        }
        jsonStr = "";
      } else {
        jsonStr += c;
      }
    }
  }

  void onRead(NimBLECharacteristic* pCharacteristic, NimBLEConnInfo& connInfo) override {
    Serial.println("📖 Read request received");
  }

  void onStatus(NimBLECharacteristic* pCharacteristic, int code) override {
    Serial.printf("🛠 Status update: %d\n", code);
    if (code == 0) { // 0 = connected
      bleConnected = true;
      Serial.println("BLE client connected");
    } else if (code == 1) { // 1 = disconnected
      bleConnected = false;
      Serial.println("BLE client disconnected");
    }
  }

  void onSubscribe(NimBLECharacteristic* pCharacteristic, NimBLEConnInfo& connInfo, uint16_t subValue) override {
    Serial.printf("🔔 Subscribed: 0x%04X\n", subValue);
  }
};


// === Display Draw Function ===
void drawBar(const char* label, int y, int value) {
    display.setCursor(0, y);
    display.print(label);
    int barWidth = map(value, 0, 100, 0, 75);
    display.fillRect(25, y, barWidth, 8, SSD1306_WHITE);
    display.setCursor(128 - 30, y);
    display.printf("%3d%%", value);
}

// === Setup Function ===
void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("Booting OLED + BLE Monitor...");

    // OLED Init
    Wire.begin();
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("OLED init failed!");
        while (true);
    }
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    // BLE Init
    NimBLEDevice::init("ESP32-PC-STATS-BLE");
    NimBLEServer* pServer = NimBLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());
    NimBLEService* pService = pServer->createService(SERVICE_UUID);

    NimBLECharacteristic* pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::WRITE // | NIMBLE_PROPERTY::WRITE_NR
    );

    pCharacteristic->setCallbacks(new StatsCallbacks());
    pService->start();

    NimBLEAdvertising* pAdvertising = NimBLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->start();

    Serial.println("✅ BLE Advertising Started");
}

// === Main Loop ===
void loop() {
    display.clearDisplay();
    if (bleConnected) {
        drawBar("CPU", 0, cpu);
        drawBar("RAM", 16, ram);
        drawBar("DISK", 32, disk);
        drawBar("NET", 48, net);
    } else {
        display.setTextSize(2);
        display.setCursor(10, 28);
        display.print("Disconnected");
        display.setTextSize(1);
    }
    display.display();
    delay(300);
}
