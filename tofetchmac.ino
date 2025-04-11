#include "WiFi.h"

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);  // Set ESP32 to station mode
    Serial.println("Starting WiFi Scanner...");
}

void loop() {
    Serial.println("\nScanning for WiFi networks...");

    int networksFound = WiFi.scanNetworks();

    if (networksFound == 0) {
        Serial.println("❌ No WiFi networks found.");
    } else {
        Serial.println("📡 WiFi Networks Found:");

        for (int i = 0; i < networksFound; i++) {
            Serial.print("SSID: ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" | MAC: ");
            Serial.print(WiFi.BSSIDstr(i));
            Serial.print(" | RSSI: ");
            Serial.print(WiFi.RSSI(i));
            Serial.println(" dBm");
        }
    }

    Serial.println("Scan Complete!\n");
    delay(5000);
}
