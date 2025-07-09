#include <Arduino.h>

#define DAC_PIN 25      // Using DAC channel 1 (GPIO25)
#define ADC_PIN 34      // Using ADC pin (GPIO34)
#define SAMPLES 360     // One sample per degree
#define AVG_SAMPLES 5   // Number of samples to average

const float PI2 = 6.283185307179586476925286766559;
byte lookupTable[SAMPLES];
unsigned long previousMillis = 0;
int currentIndex = 0;

void generateSineWave() {
  for (int i = 0; i < SAMPLES; i++) {
    lookupTable[i] = (byte)((sin(i * PI2 / SAMPLES) + 1) * 127.5);
  }
}

void setup() {
  Serial.begin(115200);
  generateSineWave();
  analogReadResolution(8);
  
  // Add some settling time
  delay(100);
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Update every 10ms (slower rate for better stability)
  if (currentMillis - previousMillis >= 10) {
    previousMillis = currentMillis;
    
    // Write DAC value
    byte outputValue = lookupTable[currentIndex];
    dacWrite(DAC_PIN, outputValue);
    
    // Read ADC value with averaging
    int inputSum = 0;
    for(int i = 0; i < AVG_SAMPLES; i++) {
      inputSum += analogRead(ADC_PIN);
      delayMicroseconds(100); // Small delay between readings
    }
    int inputValue = inputSum / AVG_SAMPLES;
    
    // Calculate difference
    int difference = inputValue - outputValue;
    
    // Print values for plotting
    Serial.print("Output:");
    Serial.print(outputValue);
    Serial.print(",Input:");
    Serial.print(inputValue);
    Serial.print(",Difference:");
    Serial.println(difference);
    
    // Update index
    currentIndex = (currentIndex + 1) % SAMPLES;
  }
}