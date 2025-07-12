
# BLE device scanner for ESP32-PC-STATS-BLE
import asyncio
from bleak import BleakScanner

async def main():
    """
    Scan for BLE devices and print their names and addresses.
    """
    print("Scanning for BLE devices...")
    devices = await BleakScanner.discover(timeout=5.0)
    for d in devices:
        print(f"Found device: {d.name} [{d.address}]")

if __name__ == "__main__":
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        print("Exiting...")
