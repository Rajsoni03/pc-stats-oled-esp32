# ESP32 Display Monitor

This folder contains the Arduino code for the ESP32 that receives system stats from your PC and displays them on an SSD1306 OLED display.

## File
- `esp32_display_monitor.ino`: Main Arduino sketch for the ESP32.

## Features
- Receives JSON-formatted stats via serial
- Displays CPU, RAM, HDD, and Network usage as bar graphs

## Requirements
- ESP32 board
- SSD1306 128x64 OLED display (I2C)
- Arduino IDE with Adafruit SSD1306, Adafruit GFX, and ArduinoJson libraries

## Usage
1. Connect the OLED display to the ESP32 via I2C (default address: 0x3C).
2. Flash the ESP32 with `esp32_display_monitor.ino`.
3. Ensure your PC is sending stats via serial using the Python script in `../pc_stats_sender/`.

## Wiring
- **VCC** → 3.3V (or 5V)
- **GND** → GND
- **SCL** → GPIO9 (ESP32-C3 default)
- **SDA** → GPIO8 (ESP32-C3 default)
