// Basic demo for accelerometer readings from Adafruit MPU6050

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define OLED_ADDR     0x3C
#define POT_PIN 34  // ESP32 analog pin for potentiometer

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  while (!Serial); // Wait for Serial Monitor

  Serial.println("Starting MPU6050 + OLED demo...");

  Wire.begin(21, 22); // ESP32 default I2C pins: SDA=21, SCL=22

  pinMode(POT_PIN, INPUT); // Initialize potentiometer pin

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("SSD1306 allocation failed");
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("MPU6050 + OLED");
  display.display();
  delay(1000);

  if (!mpu.begin()) {
    Serial.println("MPU6050 not found!");
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("MPU6050 not found!");
    display.display();
    while (1);
  } else {
    Serial.println("MPU6050 initialized.");
  }
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  int potValue = analogRead(POT_PIN); // Read potentiometer value

  Serial.print("Accel X: "); Serial.print(a.acceleration.x, 2);
  Serial.print(" Y: "); Serial.print(a.acceleration.y, 2);
  Serial.print(" Z: "); Serial.print(a.acceleration.z, 2);
  Serial.print(" | Gyro X: "); Serial.print(g.gyro.x, 2);
  Serial.print(" Y: "); Serial.print(g.gyro.y, 2);
  Serial.print(" Z: "); Serial.print(g.gyro.z, 2);
  Serial.print(" | Pot: "); Serial.println(potValue);

  display.clearDisplay();
  display.setTextSize(1);

  // Draw column headers
  display.setCursor(0, 0);
  display.println("Accel(m/s^2)");
  display.setCursor(70, 0);
  display.println("Gyro(rad/s)");

  // Draw Accel values (left column)
  display.setCursor(0, 16);
  display.print("X: "); display.println(a.acceleration.x, 2);
  display.setCursor(0, 26);
  display.print("Y: "); display.println(a.acceleration.y, 2);
  display.setCursor(0, 36);
  display.print("Z: "); display.println(a.acceleration.z, 2);

  // Draw Gyro values (right column)
  display.setCursor(70, 16);
  display.print("X: "); display.println(g.gyro.x, 2);
  display.setCursor(70, 26);
  display.print("Y: "); display.println(g.gyro.y, 2);
  display.setCursor(70, 36);
  display.print("Z: "); display.println(g.gyro.z, 2);

  // Draw Potentiometer value at the bottom
  display.setCursor(0, 54);
  display.print("Pot: ");
  display.println(potValue);

  display.display();
  delay(500);
}
