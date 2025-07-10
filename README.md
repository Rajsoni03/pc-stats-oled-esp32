# PC Stats Monitoring and Display on ESP32 OLED

Monitor your PC's CPU, RAM, Disk, and Network usage in real-time on an OLED display connected to an ESP32. The ESP32 receives system stats from your computer via serial, sent by a Python script.

## Features
- Real-time display of CPU, RAM, HDD, and Network usage as bar graphs
- Simple Python script to collect and send stats
- Easy-to-read OLED interface (SSD1306 128x64)

## Hardware Required
- ESP32 board
- SSD1306 128x64 OLED display (I2C)
- USB cable for ESP32

## Software Required
- Arduino IDE (with ESP32 board support)
- Python 3 (with `psutil` and `pyserial`)

## Wiring
Connect the OLED display to the ESP32 via I2C:

- **VCC** → 3.3V (or 5V, check your display)
- **GND** → GND
- **SCL** → GPIO9 (ESP32-C3 default)
- **SDA** → GPIO8 (ESP32-C3 default)

## Setup

### 1. Flash the ESP32
Upload `esp32.ino` to your ESP32 using the Arduino IDE. Make sure you have the following libraries installed:
- Adafruit SSD1306
- Adafruit GFX
- ArduinoJson


### 2. Install Python Dependencies
Install required Python packages using the provided `requirements.txt` file:

```bash
pip install -r requirements.txt
```

### 3. Edit Serial Port in Python Script
Update the `SERIAL_PORT` variable in `send_data.py` to match your ESP32's serial port (e.g., `/dev/cu.usbmodemXXXX` on macOS, `COMX` on Windows).

### 4. Run the Python Script
Run the script to start sending stats to the ESP32:

```bash
python send_data.py
```

## How It Works
- The Python script (`send_data.py`) collects CPU, RAM, HDD, and network usage, formats them as JSON, and sends them over serial to the ESP32.
- The ESP32 (`esp32.ino`) reads the JSON, parses the values, and displays them as bar graphs on the OLED.

## Example JSON Sent
```json
{"cpu": 23, "ram": 45, "hdd": 67, "net": 12}
```

## Troubleshooting
- If nothing appears on the display, check your wiring and I2C address (default is `0x3C`).
- Make sure the serial port in `send_data.py` matches your ESP32's port.
- Ensure the required Arduino and Python libraries are installed.

## License
MIT