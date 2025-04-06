#include <WiFi.h>

#define IN1 12
#define IN2 14
#define IN3 27
#define IN4 26
#define BLUETOOTH_RX 16  // HC-05 TX connected to ESP32 GPIO 16
#define BLUETOOTH_TX 17  // HC-05 RX connected to ESP32 GPIO 17

bool use_rssi = true;  // Start with RSSI-based movement

const char* target_mac_str = "XX:XX:XX:XX:XX:XX";  // WiFi MAC address to track

void setup() {
    Serial.begin(115200);  // For debugging
    Serial2.begin(9600, SERIAL_8N1, BLUETOOTH_RX, BLUETOOTH_TX);  // For HC-05 Bluetooth module
    WiFi.mode(WIFI_STA);  // Set ESP32 as a WiFi client

    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    // Send initial message to both Serial and Bluetooth
    printToBoth("ESP32 Ready. Waiting for RSSI movement...");
}

void loop() {
    if (Serial2.available()) {
        String msg = Serial2.readStringUntil('\n');
        msg.trim();

        if (msg == "4") {  // Left turn command
            printToBoth("Turning Left...");
            use_rssi = false;  // Stop RSSI-based movement
            turnLeft();
        }
        else if (msg == "5") {  // Right turn command
            printToBoth("Turning Right...");
            use_rssi = false;  // Stop RSSI-based movement
            turnRight();
        }
        else if (msg == "6") {  // Resume RSSI-based movement
            printToBoth("Resuming RSSI-based movement...");
            use_rssi = true;
            stopMovement();  // Stop any ongoing movement before resuming RSSI control
        }
        else if (msg == "0") {  // Stop command
            printToBoth("Stopping movement...");
            use_rssi = false;
            stopMovement();
        }
    }

    if (use_rssi) {
        scanRSSI();
    }

    delay(200);
}

void scanRSSI() {
    int n = WiFi.scanNetworks(false, true);
    int target_rssi = -100;
    bool target_found = false;

    for (int i = 0; i < n; i++) {
        if (strcmp(WiFi.BSSIDstr(i).c_str(), target_mac_str) == 0) {
            target_rssi = WiFi.RSSI(i);
            target_found = true;
            break;
        }
    }

    if (target_found) {
        String message = "Target Found! RSSI: " + String(target_rssi);
        printToBoth(message);

        if (target_rssi > -45) {
            printToBoth("Stopping...");
            stopMovement();
        } else {
            printToBoth("Moving Forward...");
            moveForward();
        }
    } else {
        printToBoth("Target not found...");
        stopMovement();
    }
}

// Helper function to print to both Serial and Bluetooth
void printToBoth(const char* message) {
    Serial.println(message);
    Serial2.println(message);
}

void printToBoth(String message) {
    Serial.println(message);
    Serial2.println(message);
}

void stopMovement() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

void moveForward() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void turnLeft() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void turnRight() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}