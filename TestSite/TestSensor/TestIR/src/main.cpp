#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <IRrecv.h>
#include <IRutils.h>

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// IR receiver pin
#define IR_RECEIVE_PIN  14  // Change to your IR receiver pin

IRrecv irrecv(IR_RECEIVE_PIN);
decode_results results;

void setup() {
  Serial.begin(115200);

  // Initialize OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("IR Remote Test");
  display.display();

  // Initialize IR receiver
  irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode(&results)) {
    // Print raw data to Serial
    Serial.print("IR Data: 0x");
    Serial.println(results.value, HEX);

    // Show on OLED
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("IR Remote Test");
    display.setCursor(0,20);
    display.print("Code: 0x");
    display.println((uint32_t)results.value, HEX);
    display.display();

    irrecv.resume(); // Receive the next value
  }
}