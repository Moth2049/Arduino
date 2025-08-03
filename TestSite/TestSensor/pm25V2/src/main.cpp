#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DHTPIN 4      // GPIO4 for DHT22 data
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

SoftwareSerial mySerial(3, 1); // RX, TX

unsigned int pm1 = 0;
unsigned int pm2_5 = 0;
unsigned int pm10 = 0;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  // OLED init
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // DHT init
  dht.begin();
}

void loop() {
  int index = 0;
  char value;
  char previousValue;

  while (mySerial.available()) {
    value = mySerial.read();
    if ((index == 0 && value != 0x42) || (index == 1 && value != 0x4d)) {
      Serial.println("Cannot find the data header.");
      break;
    }

    if (index == 4 || index == 6 || index == 8 || index == 10 || index == 12 || index == 14) {
      previousValue = value;
    }
    else if (index == 5) {
      pm1 = 256 * previousValue + value;
    }
    else if (index == 7) {
      pm2_5 = 256 * previousValue + value;
    }
    else if (index == 9) {
      pm10 = 256 * previousValue + value;
    } else if (index > 15) {
      break;
    }
    index++;
  }
  while (mySerial.available()) mySerial.read();

  // Read DHT22
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  // Serial output
  Serial.print("{ ");
  Serial.print("\"pm1\": "); Serial.print(pm1); Serial.print(" ug/m3, ");
  Serial.print("\"pm2_5\": "); Serial.print(pm2_5); Serial.print(" ug/m3, ");
  Serial.print("\"pm10\": "); Serial.print(pm10); Serial.print(" ug/m3, ");
  Serial.print("\"temp\": "); Serial.print(temp); Serial.print(" C, ");
  Serial.print("\"hum\": "); Serial.print(hum); Serial.println(" % }");

  // OLED output
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("PM1: "); display.print(pm1); display.println(" ug/m3");
  display.print("PM2.5: "); display.print(pm2_5); display.println(" ug/m3");
  display.print("PM10: "); display.print(pm10); display.println(" ug/m3");
  display.print("T: "); display.print(temp); display.print("C ");
  display.print("H: "); display.print(hum); display.println("%");
  display.display();

  delay(1000);
}