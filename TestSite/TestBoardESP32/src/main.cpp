#include <Arduino.h>

void setup() {
  Serial.begin(9600); // Start serial communication at 115200 baud
  while (!Serial) {
    ; // Wait for serial port to connect. Needed for native USB
  }
}

void loop() {
  Serial.println("Board is alive!"); // Print message every second
  delay(1000); // Wait for 1 second
}

