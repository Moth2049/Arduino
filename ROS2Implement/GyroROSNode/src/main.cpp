#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define OLED_ADDR     0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Wire.begin(21, 22);
  mpu.begin();  // assume AD0→GND → 0x68

  // OLED init
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // 1) Update OLED
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Accel (m/s^2)   Gyro (rad/s)");
  display.setCursor(0,16);
  display.printf("X:%5.2f   X:%5.2f\n", a.acceleration.x, g.gyro.x);
  display.printf("Y:%5.2f   Y:%5.2f\n", a.acceleration.y, g.gyro.y);
  display.printf("Z:%5.2f   Z:%5.2f\n", a.acceleration.z, g.gyro.z);
  display.display();

  // 2) Emit CSV: ax,ay,az,gx,gy,gz
  Serial.printf(
    "%f,%f,%f,%f,%f,%f\n",
    a.acceleration.x,
    a.acceleration.y,
    a.acceleration.z,
    g.gyro.x,
    g.gyro.y,
    g.gyro.z
  );

  delay(20); // ~50 Hz
}
