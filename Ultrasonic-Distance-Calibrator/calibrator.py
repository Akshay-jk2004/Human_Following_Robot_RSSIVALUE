# calibrator.py

import serial
import time

SERIAL_PORT = 'COM4'       # Change this to your port: 'COM3', '/dev/ttyUSB0', etc.
BAUD_RATE = 115200

def parse_distance(line):
    if line.startswith("DIST:"):
        try:
            return float(line.strip().split(":")[1])
        except (ValueError, IndexError):
            return None
    return None

def calibrate():
    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        print(f"[INFO] Connected to {SERIAL_PORT}. Listening for distance values...")
        time.sleep(2)

        while True:
            if ser.in_waiting:
                line = ser.readline().decode('utf-8').strip()
                distance = parse_distance(line)
                if distance is not None:
                    print(f"📏 Distance: {distance:.2f} cm")

                    # Decision logic
                    if distance > 100:
                        print("✅ Action: Move Forward")
                    elif distance < 30:
                        print("⛔ Action: Move Backward")
                    else:
                        print("⏸️ Action: Hold Position")

                    print("-" * 30)
            time.sleep(0.5)

    except serial.SerialException as e:
        print(f"[ERROR] Could not open port {SERIAL_PORT}: {e}")
    except KeyboardInterrupt:
        print("\n[INFO] Calibration stopped by user.")

if __name__ == "__main__":
    calibrate()
