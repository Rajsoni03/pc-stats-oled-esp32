# PC Stats Sender

This folder contains Python scripts that collect system stats from your PC and send them to the ESP32 via UART (serial) or BLE (Bluetooth Low Energy).

## Files
- `system_monitor_sender.py`: UART sender script
- `system_monitor_sender_ble.py`: BLE sender script
- `system_monitor_sender_ble_scan.py`: BLE scanner utility

## Features
- Collects CPU, RAM, HDD, and Network usage
- Sends stats as JSON over UART (serial) or BLE

## Requirements
- Python 3
- `psutil`, `pyserial` (for UART), `bleak` (for BLE)
- Install all dependencies via:
  ```bash
  pip install -r ../requirements.txt
  ```

## Usage
### UART (Serial)
1. Edit the `SERIAL_PORT` variable in `system_monitor_sender.py` to match your ESP32's port.
2. Run the script:
   ```bash
   python system_monitor_sender.py
   ```
3. The script will print and send stats to the ESP32 every second.

### BLE
1. Edit the BLE device address in `system_monitor_sender_ble.py` if needed.
2. Run the script:
   ```bash
   python system_monitor_sender_ble.py
   ```
3. Use `system_monitor_sender_ble_scan.py` to scan for available BLE devices if needed.
4. See the main README for more details and troubleshooting.