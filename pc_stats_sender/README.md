# PC Stats Sender

This folder contains the Python script that collects system stats from your PC and sends them to the ESP32 via serial.

## File
- `system_monitor_sender.py`: Python script to collect and send stats.

## Features
- Collects CPU, RAM, HDD, and Network usage
- Sends stats as JSON over serial

## Requirements
- Python 3
- `psutil` and `pyserial` (install via `pip install -r ../requirements.txt`)

## Usage
1. Edit the `SERIAL_PORT` variable in `system_monitor_sender.py` to match your ESP32's port.
2. Run the script:
   ```bash
   python system_monitor_sender.py
   ```
3. The script will print and send stats to the ESP32 every second.
