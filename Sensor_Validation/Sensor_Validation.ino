#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup() {

  Serial.begin(115200);
  Wire.begin();

  mpu.initialize();

  Serial.println("Sensor initialized");
}

void loop() {

  int16_t ax, ay, az;

  mpu.getAcceleration(&ax, &ay, &az);

  Serial.print("Ax: ");
  Serial.print(ax);

  Serial.print("  Ay: ");
  Serial.print(ay);

  Serial.print("  Az: ");
  Serial.println(az);

  delay(200);
}