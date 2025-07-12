
# PC Stats OLED ESP32

Monitor your PC's CPU, RAM, Disk, and Network usage in real-time on an OLED display connected to an ESP32. The ESP32 receives system stats from your computer via serial, sent by a Python script.

## Features
- Real-time display of CPU, RAM, HDD, and Network usage as bar graphs
- Simple Python script to collect and send stats
- Easy-to-read OLED interface (SSD1306 128x64)

## Folder Structure

```
pc-stats-oled-esp32/
├── esp32_display_monitor/
│   ├── esp32_display_monitor.ino
│   └── README.md
├── pc_stats_sender/
│   ├── system_monitor_sender.py
│   └── README.md
├── requirements.txt
└── README.md (this file)
```

## Quick Start

1. See [`esp32_display_monitor/README.md`](esp32_display_monitor/README.md) for ESP32 setup and wiring.
2. See [`pc_stats_sender/README.md`](pc_stats_sender/README.md) for Python sender setup.
3. Install Python dependencies:
   ```bash
   pip install -r requirements.txt
   ```
4. Flash the ESP32 and run the Python sender script.

## Wiring
Connect the OLED display to the ESP32 via I2C:

- **VCC** → 3.3V (or 5V, check your display)
- **GND** → GND
- **SCL** → GPIO9 (ESP32-C3 default)
- **SDA** → GPIO8 (ESP32-C3 default)

## Setup

## License
MIT