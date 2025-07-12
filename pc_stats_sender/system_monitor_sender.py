import psutil
import serial
import time
import json

SERIAL_PORT = '/dev/cu.usbmodem2101'  # Update as per your port
BAUD_RATE = 115200
HDD_MOUNTPOINT = '/'

def get_stats():
    cpu = psutil.cpu_percent(interval=0.5) # Get CPU usage over 0.5 seconds
    mem = psutil.virtual_memory().percent
    hdd = psutil.disk_usage(HDD_MOUNTPOINT).percent

    net1 = psutil.net_io_counters()
    time.sleep(0.5)  # wait for a short period to get a better network speed reading
    net2 = psutil.net_io_counters()
    net_speed_kbps = (net2.bytes_recv - net1.bytes_recv + net2.bytes_sent - net1.bytes_sent) / 1024 * 2  # KB/s (2x because we measure over 0.5 seconds)
    net_speed = (net_speed_kbps) / (1_000)  # Convert KB/s to MB/s

    MAX_SPEED_MBPS = 120 # Maximum expected network speed in MB/s
    net_percent = min(100, int((net_speed / MAX_SPEED_MBPS) * 100))

    return {
        "cpu": int(cpu),
        "ram": int(mem),
        "hdd": int(hdd),
        "net": int(net_percent)
    }

def main():
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    time.sleep(2)  # wait for ESP32 to reset

    while True:
        stats = get_stats()
        json_data = json.dumps(stats)
        ser.write((json_data + '\n').encode('utf-8'))
        print("Sent:", json_data)


if __name__ == "__main__":
    main()
