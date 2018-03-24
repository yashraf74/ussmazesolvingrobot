
#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

// Timers
unsigned long timer = 0;
float timeStep = 0.01;

// Yaw values

float yaw = 0;



#include <Ultrasonic.h>

/*
   ex.: Ultrasonic ultrasonic1 (trigpin, echopin)
*/

Ultrasonic FUSS(11, 12);
Ultrasonic RUSS(4, 8);
Ultrasonic LUSS(13, 7);

int sor3aR = 200;                      //variable representing pwm (speed) for analog write.
int sor3aL = sor3aR - 2;
int minDistance4USS = 25;
int choice = 4;                       //choice to turn either left or right, 4 represents left and 6 represents right.
int in1 = 5;
int in2 = 3;
int in3 = 9;
int in4 = 6;
int input = 0;


void setup()
{
  // Initialize MPU6050
  while (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }

  // Calibrate gyroscope. The calibration must be at rest.
  // If you don't want calibrate, comment this line.
  mpu.calibrateGyro();

  // Set threshold sensivty. Default 3.
  // If you don't want use threshold, comment this line or set 0.
  // mpu.setThreshold(3);



  Serial.begin(115200);
}

void loop()
{


  while (!isFUSSnear())
  {
    moveF();
    Serial.println("robot is walking forward ");
    //  delay(500);
  }

  if (isRUSSnear() && !isLUSSnear())
  {
    moveL();
    Serial.println("robot is turning left ");
  }

  else if (!isRUSSnear() && isLUSSnear())
  {
    moveR();
    Serial.println("robot is turning right ");
    //Serial.print(L);
  }

  else if (isRUSSnear() && isLUSSnear())
  {
    Serial.println("robot is bylef w yerga3 ");
    lefwerga3();
    swap(choice);
  }

  else if (!isRUSSnear() && !isLUSSnear())
  {
    turn(choice);
    Serial.print("robot is turning  ");
    Serial.println(choice);
  }

  // delay(500);
}

bool isFUSSnear()
{
  if (FUSS.distanceRead() < minDistance4USS && FUSS.distanceRead() > 0)
    //Serial.println("obstacle is near");
    return true;
  else
    //Serial.println("no obstacle ahead");
    return false;
}

bool isRUSSnear()
{
  if (RUSS.distanceRead() < minDistance4USS && RUSS.distanceRead() > 0)
    //Serial.println("obstacle is near");
    return true;
  else
    //Serial.println("no obstacle ahead");
    return false;
}

bool isLUSSnear()
{
  if (LUSS.distanceRead() < minDistance4USS && LUSS.distanceRead() > 0)
    //Serial.println("obstacle is near");
    return true;
  else
    //Serial.println("no obstacle ahead");
    return false;
}

void moveF()
{
  analogWrite(in1, sor3aR);
  analogWrite(in2, 0);
  analogWrite(in3, sor3aL);
  analogWrite(in4, 0);
}

void moveB()
{
  analogWrite(in1, 0);
  analogWrite(in2, sor3aR);
  analogWrite(in3, 0);
  analogWrite(in4, sor3aL);
}

void moveL()
{
  float initVal;
  initVal = yawVal();
  while ( yawVal() < (initVal + 90)) {
    Serial.print("initValL =  "); Serial.println(initVal);
    Serial.print(" yawValL =  "); Serial.println(yawVal());
    analogWrite(in1, sor3aR);
    analogWrite(in2, 0);
    analogWrite(in3, 0);
    analogWrite(in4, sor3aL);
  }

}

void moveR()
{
  float initVal;
  initVal = yawVal();
  while ( yawVal() > (initVal - 90)) {
    Serial.print("initValR =  "); Serial.println(initVal);
    Serial.print(" yawValR =  "); Serial.println(yawVal());

    analogWrite(in1, 0);
    analogWrite(in2, sor3aR);
    analogWrite(in3, sor3aL);
    analogWrite(in4, 0);
  }

}

void Stop()
{
  analogWrite(in1, 0);
  analogWrite(in2, 0);
  analogWrite(in3, 0);
  analogWrite(in4, 0);
}

void lefwerga3()
{
  moveR();
  moveR();
}

void turn(int x)
{
  if (x == 6)
    moveR();
  else if ( x == 4)
    moveL();
  else
    Stop();

}

void swap(int x)
{
  if (x == 4)
    choice = 6;
  else if (x == 6)
    choice = 4;
}

float yawVal() {
  timer = millis();

  // Read normalized values
  Vector norm = mpu.readNormalizeGyro();

  // Calculate Pitch, Roll and Yaw
  yaw = yaw + norm.ZAxis * timeStep;



  // Wait to full timeStep period
  delay((timeStep * 1000) - (millis() - timer));
  return yaw;
}


