# ESP32 Display Monitor

This folder contains the Arduino code for the ESP32 that receives system stats from your PC and displays them on an SSD1306 OLED display. Supports both UART (serial) and BLE (Bluetooth Low Energy) communication.

## Files
- `esp32_display_monitor.ino`: UART (serial) firmware for ESP32.
- `esp32_display_monitor_ble.ino`: BLE firmware for ESP32.

## Features
- Receives JSON-formatted stats via UART (serial) or BLE
- Displays CPU, RAM, HDD, and Network usage as bar graphs

## Requirements
- ESP32 board
- SSD1306 128x64 OLED display (I2C)
- Arduino IDE with Adafruit SSD1306, Adafruit GFX, and ArduinoJson libraries

## Usage
1. Connect the OLED display to the ESP32 via I2C (default address: 0x3C).
2. Flash the ESP32 with the appropriate firmware:
   - For UART: `esp32_display_monitor.ino`
   - For BLE: `esp32_display_monitor_ble.ino`
3. Ensure your PC is sending stats using the matching Python script in `../pc_stats_sender/`.

## Wiring
- **VCC** → 3.3V (or 5V)
- **GND** → GND
- **SCL** → GPIO9 (ESP32-C3 default)
- **SDA** → GPIO8 (ESP32-C3 default)

## Communication
- **UART (Serial):** Connect ESP32 to PC via USB. Stats are sent over serial.
- **BLE:** ESP32 acts as BLE server. Stats are sent wirelessly from PC.

See the main README for more details and troubleshooting.
