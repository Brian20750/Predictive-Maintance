#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

unsigned long previousTime = 0; //stores previous time for interval calcuations
const int interval = 20; // interval distance of choice (ms), 50hz sampling
void setup() {
  Serial.begin(115200);   // 115200 is a fast enough speed to handle many samples per second without losing data.
  
  Wire.begin();           // Initialize I2C communication bus
  mpu.initialize();       // Initialize the MPU6050/6500 sensor
  Serial.println("Sensor initialized"); //displays start (helps with debugging)
}

void loop() {
  unsigned long currentTime = millis(); // current time in ms

   // Check if enough time has passed between samples
  if (currentTime - previousTime >= interval) {
    previousTime = currentTime; // Update the sample time

    int16_t ax, ay, az;       // Variables to store raw accelerometer readings
    mpu.getAcceleration(&ax, &ay, &az); // Read accelerometer data

    // Print data in CSV format (time, ax, ay, az)
    Serial.print(currentTime); // Print timestamp
    Serial.print(",");
    Serial.print(ax);          // Print X-axis acceleration
    Serial.print(",");
    Serial.print(ay);          // Print Y-axis acceleration
    Serial.print(",");
    Serial.println(az);        // Print Z-axis acceleration
  }
}