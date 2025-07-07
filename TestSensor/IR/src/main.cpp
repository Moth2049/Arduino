#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

const uint16_t kRecvPin = 15;  // IR receiver output pin connected to GPIO 15

IRrecv irrecv(kRecvPin);
decode_results results;

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn();  // Start the receiver
  Serial.println("IR Receiver ready...");
}

void loop() {
  if (irrecv.decode(&results)) {
    // Print raw data
    Serial.println(resultToHumanReadableBasic(&results));
    Serial.println(resultToSourceCode(&results));  // Raw data for replay or analysis
    Serial.println("");  // Blank line between readings

    irrecv.resume();  // Receive the next value
  }
}
