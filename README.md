# 🤖 AURA - Autonomous Utility Robotic Assistant

AURA is an intelligent, semi-autonomous robotic system built using **ESP32**, capable of navigating towards a target based on **Wi-Fi RSSI (signal strength)** and avoiding obstacles using **ultrasonic sensors**. Designed as a prototype for applications like smart assistance, autonomous delivery, and environmental monitoring, AURA combines wireless localization and real-time obstacle detection to demonstrate practical robotic autonomy.

## 🏆 Achievements

- 🥈 Secured **Second Prize** at the **Robotic Expo2025** conducted by the **Department of Artificial Intelligence and Data Science**, **Muthoot Institute of Technology and Science.**

---

## 📌 Features

- 📶 **Wi-Fi RSSI-Based Navigation** – Follows the signal strength of a target device (e.g., a hotspot-enabled phone).
- 🚧 **Obstacle Detection** – Ultrasonic sensors prevent collisions and reroute the robot dynamically.
- 🔁 **Dynamic Mode Switching** – Accepts Bluetooth commands to pause/resume RSSI-based movement or manually override for specific actions.
- 🔋 Energy-efficient control using ESP32 and L298N motor driver.

---

## 🛠️ Hardware Requirements

- ESP32 Dev Module  
- HC-05 Bluetooth Module  
- L298N Motor Driver  
- 2 DC Geared Motors  
- Ultrasonic Sensor (HC-SR04)  
- Chassis with wheels  
- 12V Battery or power supply  
- Jumper wires, Breadboard  
- Smartphone (for Wi-Fi hotspot & Bluetooth app)

---

## 🔌 Pin Connections

### 🔹 ESP32 to L298N Motor Driver:
| L298N Pin | ESP32 Pin |
|-----------|------------|
| IN1       | D12 (GPIO12) |
| IN2       | D14 (GPIO14) |
| IN3       | D27 (GPIO27) |
| IN4       | D26 (GPIO26) |

### 🔹 ESP32 to HC-05 Bluetooth Module:
| HC-05 Pin | ESP32 Pin |
|-----------|------------|
| TX        | D4 (GPIO4)  |
| RX        | D2 (GPIO2)  |

*Use a voltage divider on the RX line of HC-05 to avoid overvoltage from ESP32’s 3.3V logic.*

### 🔹 ESP32 to Ultrasonic Sensor:
| HC-SR04 Pin | ESP32 Pin |
|-------------|------------|
| TRIG        | D18 (GPIO18) |
| ECHO        | D19 (GPIO19) |

---

## 📦 Software Requirements

- **Arduino IDE** (Latest version)
- **ESP32 Board Package** (Install via Board Manager)
- **Bluetooth Serial Terminal App** (for testing on Android)

### 🧩 Arduino Libraries Required

Install these libraries from the Arduino Library Manager:

- `WiFi.h` (comes with ESP32 board package)
- `BluetoothSerial.h` (also comes with ESP32 package)
- `Wire.h` (standard library)
- `NewPing` *(optional for ultrasonic handling, or you can use direct pulseIn method)*

---

## 📂 Project Structure

