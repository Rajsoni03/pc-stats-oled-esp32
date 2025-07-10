#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <ArduinoJson.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1  // No reset pin
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int cpu = 0, ram = 0, disk = 0, net = 0;

void drawBar(const char* label, int y, int value) {
  display.setCursor(0, y);
  display.print(label);

  // Label area: 20px, Bar width: 75px
  int barWidth = map(value, 0, 100, 0, 75);
  display.fillRect(25, y, barWidth, 8, SSD1306_WHITE);

  // Draw percentage value
  display.setCursor(128 - 24, y);
  display.print(value);
  display.print("%");
}

void setup() {
  Serial.begin(115200);
  Wire.begin();  // SDA, SCL default: GPIO8, GPIO9 for ESP32-C3
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  static String jsonStr = "";
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      StaticJsonDocument<200> doc;
      DeserializationError error = deserializeJson(doc, jsonStr);
      if (!error) {
        cpu = doc["cpu"];
        ram = doc["ram"];
        disk = doc["hdd"];
        net = doc["net"];
      }
      jsonStr = "";
    } else {
      jsonStr += c;
    }
  }

  display.clearDisplay();
  drawBar("CPU", 0, cpu);
  drawBar("RAM", 16, ram);
  drawBar("HDD", 32, disk);
  drawBar("NET", 48, net);
  display.display();
}

