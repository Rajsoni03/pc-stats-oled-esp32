#!/usr/bin/env python3

import psutil
import time
import json
import sys
import asyncio
from bleak import BleakClient, BleakScanner

SERVICE_UUID = "12345678-1234-1234-1234-123456789abc"
CHARACTERISTIC_UUID = "abcdefab-1234-1234-1234-abcdefabcdef"
HDD_MOUNTPOINT = '/'
DEVICE_NAME = "ESP32-PC-STATS-BLE"

async def get_stats():
    """
    Collect system stats: CPU, RAM, HDD, and Network usage.
    Returns a dictionary with integer values for each stat.
    """
    # CPU usage
    try:
        cpu = psutil.cpu_percent(interval=0.5)
    except Exception as e:
        print(f"Error getting CPU usage: {e}", file=sys.stderr)
        cpu = 0

    # RAM usage
    try:
        ram = psutil.virtual_memory().percent
    except Exception as e:
        print(f"Error getting memory usage: {e}", file=sys.stderr)
        ram = 0

    # HDD usage
    try:
        disk = psutil.disk_usage(HDD_MOUNTPOINT).percent
    except Exception as e:
        print(f"Error getting disk usage: {e}", file=sys.stderr)
        disk = 0

    # Network usage (as percent of max speed)
    try:
        net1 = psutil.net_io_counters()
        time.sleep(0.5)  # wait for a short period to get a better network speed reading
        net2 = psutil.net_io_counters()
        net_speed_kbps = (net2.bytes_recv - net1.bytes_recv + net2.bytes_sent - net1.bytes_sent) / 1024 * 2  # KB/s (2x because we measure over 0.5 seconds)
        net_speed = net_speed_kbps / 1000 # Convert KB/s to MB/s
        MAX_SPEED_MBPS = 120 # Maximum expected network speed in MB/s
        net = min(100, int((net_speed / MAX_SPEED_MBPS) * 100))
    except Exception as e:
        print(f"Error getting network stats: {e}", file=sys.stderr)
        net = 0

    return {
        "cpu": int(cpu),
        "ram": int(ram),
        "hdd": int(disk),
        "net": int(net)
    }

async def main():
    """
    Main loop: scan for ESP32 BLE device and send system stats as JSON.
    """
    print("Scanning for ESP32 BLE device...")
    devices = await BleakScanner.discover(timeout=5.0)
    target = None
    for d in devices:
        if d.name and DEVICE_NAME in d.name:
            target = d
            break
    if not target:
        print("ESP32 BLE device not found.", file=sys.stderr)
        sys.exit(1)
    print(f"Found device: {target.name} [{target.address}]")

    async with BleakClient(target.address) as client:
        print("Connected to ESP32 BLE!")
        while True:
            stats = await get_stats()
            json_data = json.dumps(stats) + '\n'
            try:
                await client.write_gatt_char(CHARACTERISTIC_UUID, json_data.encode('utf-8'))
                print(f"Sent: {json_data.strip()}")
            except Exception as e:
                print(f"BLE write error: {e}", file=sys.stderr)
                break

if __name__ == "__main__":
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        print("Exiting...")
    except Exception as e:
        print(f"Fatal error: {e}", file=sys.stderr)
