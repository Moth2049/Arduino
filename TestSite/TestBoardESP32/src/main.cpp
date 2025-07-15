#include <Arduino.h>

#define LED_PIN 2 // Onboard LED for most ESP32 boards

void setup() {
  Serial.begin(9600); // Start serial communication at 9600 baud
  while (!Serial) {
    ; // Wait for serial port to connect. Needed for native USB
  }
  pinMode(LED_PIN, OUTPUT); // Set onboard LED as output
}

void loop() {
  Serial.println("Board is alive!"); // Print message every second
  digitalWrite(LED_PIN, HIGH); // Turn LED on
  delay(500); // Wait 0.5 second
  digitalWrite(LED_PIN, LOW); // Turn LED off
  delay(500); // Wait

}