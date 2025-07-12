
# PC Stats OLED ESP32

Monitor your PC's CPU, RAM, Disk, and Network usage in real-time on an OLED display connected to an ESP32. The ESP32 receives system stats from your computer via either UART (serial) or BLE (Bluetooth Low Energy), sent by a Python script.


## Features
- Real-time display of CPU, RAM, HDD, and Network usage as bar graphs
- Simple Python scripts to collect and send stats (UART and BLE)
- Easy-to-read OLED interface (SSD1306 128x64)
- Supports both UART (serial) and BLE (Bluetooth Low Energy) communication

pc-stats-oled-esp32/

## Folder Structure

```
pc-stats-oled-esp32/
├── esp32_display_monitor/
│   ├── esp32_display_monitor.ino         # UART (serial) version for ESP32
│   ├── esp32_display_monitor_ble.ino     # BLE version for ESP32
│   └── README.md
├── pc_stats_sender/
│   ├── system_monitor_sender.py          # UART sender script
│   ├── system_monitor_sender_ble.py      # BLE sender script
│   ├── system_monitor_sender_ble_scan.py # BLE scanner utility
│   └── README.md
├── requirements.txt
└── README.md (this file)
```


## Quick Start

1. See [`esp32_display_monitor/README.md`](esp32_display_monitor/README.md) for ESP32 setup, wiring, and flashing instructions for both UART and BLE.
2. See [`pc_stats_sender/README.md`](pc_stats_sender/README.md) for Python sender setup and usage (UART and BLE).
3. Install Python dependencies:
   ```bash
   pip install -r requirements.txt
   ```
4. Flash the appropriate ESP32 firmware:
   - For UART: `esp32_display_monitor.ino`
   - For BLE: `esp32_display_monitor_ble.ino`
5. Run the corresponding Python sender script:
   - For UART: `system_monitor_sender.py`
   - For BLE: `system_monitor_sender_ble.py`


## Wiring
Connect the OLED display to the ESP32 via I2C:

- **VCC** → 3.3V (or 5V, check your display)
- **GND** → GND
- **SCL** → GPIO9 (ESP32-C3 default)
- **SDA** → GPIO8 (ESP32-C3 default)

## Communication
- **UART (Serial):** Connect your ESP32 to your PC via USB. The Python sender script will send stats over serial.
- **BLE:** ESP32 acts as a BLE server. The Python sender script connects and sends stats wirelessly.

## Setup
- Choose your preferred communication method (UART or BLE).
- Flash the matching ESP32 firmware and run the corresponding Python sender script.
- See subfolder READMEs for more details and troubleshooting.

## License
MIT