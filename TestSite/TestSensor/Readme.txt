// Add to setup() after Wire.begin();
Wire.beginTransmission(MPU_ADDR);
Wire.write(0x75); // WHO_AM_I register
Wire.endTransmission(false);
Wire.requestFrom(MPU_ADDR, 1, true);
uint8_t whoami = Wire.read();
Serial.print("WHO_AM_I: 0x");
Serial.println(whoami, HEX);

this code section use to see what address gyro is used