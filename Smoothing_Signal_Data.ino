#include <Wire.h>
#include <MPU6050.h>
#include <math.h>

MPU6050 mpu;

unsigned long previousTime = 0; //stores previous time for interval calcuations
const int interval = 20; // interval distance of choice (ms), 50hz sampling

const int N = 5;        //Number of samples to avg

//array to store data points to average
  int axArray[5] = {0};
  int ayArray[5] = {0};
  int azArray[5] = {0};

// variables to store avg data points and a counter to help with code
  int count = 0;
  int axAvg = 0;
  int ayAvg = 0;
  int azAvg = 0;

void setup() {
  Serial.begin(115200);   // 115200 is a fast enough speed to handle many samples per second without losing data.
  
  Wire.begin();           // Initialize I2C communication bus
  mpu.initialize();       // Initialize the MPU6050/6500 sensor
  Serial.println("Sensor initialized"); //displays start (helps with debugging)
}

//finds the average in the array
void computeAvg(){
    long sumAx = 0;
    long sumAy = 0;
    long sumAz = 0;

    // Compute the sum of the last 5 readings
    for (int i = 0; i < 5; i++) {
        sumAx += axArray[i];
        sumAy += ayArray[i];
        sumAz += azArray[i];
    }

    // Compute averages
    axAvg = sumAx / 5;
    ayAvg = sumAy / 5;
    azAvg = sumAz / 5;
}


void loop() {
  unsigned long currentTime = millis();   // Current time in ms

  // Check if enough time has passed
  if (currentTime - previousTime >= interval) {
    previousTime = currentTime;           // Update last sample time

    int16_t ax, ay, az;                   // Raw sensor readings
    mpu.getAcceleration(&ax, &ay, &az);   // Read sensor

    //store sensor value into array
    axArray[count] = ax;
    ayArray[count] = ay;
    azArray[count] = az;

    // Move to next index
    count++;
    //resets count to allow for new values to loop into the array
    if (count >= N){
      count = 0;
    } 
    
    //Solves for the average
    computeAvg();

    //Overall vibration value
    float vibration = sqrt((float)axAvg*axAvg + (float)ayAvg*ayAvg + (float)azAvg*azAvg);

    // Format: time(ms), axAvg, ayAvg, azAvg, vibration
    Serial.print("Current Time:");
    Serial.print(currentTime);
    Serial.print(", ");

    Serial.print("Ax:");
    Serial.print(axAvg);
    Serial.print(", ");

    Serial.print("Ay:");
    Serial.print(ayAvg);
    Serial.print(", ");

    Serial.print("Az:");
    Serial.print(azAvg);
    Serial.print(", ");

    Serial.print("Vibration:");
    Serial.println(vibration);
  }
}