#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const uint16_t kRecvPin = 15;  // IR receiver output pin connected to GPIO 15
IRrecv irrecv(kRecvPin);
decode_results results;

void setup() {
  Serial.begin(115200);
  pinMode(kRecvPin, INPUT_PULLDOWN);  // Ensure a defined logic level when idle

  // Start IR receiver
  irrecv.enableIRIn();

  // OLED init
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);  // Halt
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Waiting for IR...");
  display.display();

  Serial.println("IR Ready.");
}

void loop() {
  if (irrecv.decode(&results)) {
    // IR signal detected!
    Serial.println("IR Signal detected!");

    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.println("IR Signal!");
    display.display();

    delay(1000);  // Keep message for a moment

    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println("Waiting for IR...");
    display.display();

    irrecv.resume();  // Ready for next signal
  }
}
