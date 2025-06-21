#include <Arduino.h>

#define OUTPUT_PIN  12   // Pin to send digital output
#define INPUT_PIN   13   // Pin to receive digital input

unsigned long previousOutputMillis = 0;
unsigned long previousPrintMillis = 0;
const unsigned long outputInterval = 1000; // 1 second
const unsigned long pulseDuration = 1000;   // 100 ms pulse
bool outputState = LOW;

void setup() {
  pinMode(OUTPUT_PIN, OUTPUT);
  pinMode(INPUT_PIN, INPUT);
  Serial.begin(115200);
}

void loop() {
  unsigned long currentMillis = millis();

  // Handle output pulse
  if (!outputState && (currentMillis - previousOutputMillis >= outputInterval)) {
    digitalWrite(OUTPUT_PIN, HIGH);
    outputState = HIGH;
    previousOutputMillis = currentMillis;
  }
  if (outputState && (currentMillis - previousOutputMillis >= pulseDuration)) {
    digitalWrite(OUTPUT_PIN, LOW);
    outputState = LOW;
  }

  // Print input state every 100ms
  if (currentMillis - previousPrintMillis >= 100) {
    int inputState = digitalRead(INPUT_PIN);
    Serial.print("Input pin state: ");
    Serial.println(inputState);
    previousPrintMillis = currentMillis;
  }
}