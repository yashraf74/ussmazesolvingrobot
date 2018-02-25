/*
 * Ultrasonic Simple
 * Prints the distance read by an ultrasonic sensor in
 * centimeters. They are supported to four pins ultrasound
 * sensors (liek HC-SC04) and three pins (like PING)))
 * and Seeed Studio sesores).
 *
 * The circuit:
 * * Module HR-SC04 (four pins) or PING))) (and other with
 *   three pins), attached to digital pins as follows:
 * ---------------------    ---------------------
 * | HC-SC04 | Arduino |    | 3 pins  | Arduino |
 * ---------------------    ---------------------
 * |   Vcc   |   5V    |    |   Vcc   |   5V    |
 * |   Trig  |   12    | OR |   SIG   |   13    |
 * |   Echo  |   13    |    |   Gnd   |   GND   |
 * |   Gnd   |   GND   |    ---------------------
 * ---------------------
 * Note: You need not obligatorily use the pins defined above
 * 
 * By default, the distance returned by the distanceRead()
 * method is in centimeters, to get the distance in inches,
 * pass INC as a parameter.
 * Example: ultrasonic.distanceRead(INC)
 *
 * created 3 Apr 2014
 * by Erick Simões (github: @ErickSimoes | twitter: @AloErickSimoes)
 * modified 23 Jan 2017
 * by Erick Simões (github: @ErickSimoes | twitter: @AloErickSimoes)
 * modified 03 Mar 2017
 * by Erick Simões (github: @ErickSimoes | twitter: @AloErickSimoes)
 *
 * This example code is released into the MIT License.
 */

#include <Ultrasonic.h>

/*
 * Pass as a parameter the trigger and echo pin, respectively,
 * or only the signal pin (for sensors 3 pins), like:
 * Ultrasonic ultrasonic(13);
 */
Ultrasonic FUSS(12, 11);
Ultrasonic RUSS(4, 2);
Ultrasonic LUSS(13, 7);
int R = 6;
int L = 4;
int in1 = 3;
int in2 = 5;
int in3 = 6;
int in4 = 9;
int input=0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  //Serial.print("Distance in CM: ");
  // Pass INC as a parameter to get the distance in inches
  //Serial.println(a7amada.distanceRead());
  //moveF();
  // Serial.print("robot is walking forward ");
  if (isFUSSnear())
  {
    if (isRUSSnear())
    {
       if(isLUSSnear())      
       {
       Serial.println("robot is bylef w yerga3 ");
       swap(R,L);  
       }
       else 
       {
       moveL();
       Serial.println("robot is turning left ");
        //Serial.print(L);
       }
    }
    else
    {
    turn(R);
     Serial.println("robot is turning ");
        Serial.print(R);
    }
  }
  else
  {
    moveF();
    Serial.println("robot is walking forward ");
  }  
  delay(2000);
}

bool isFUSSnear()
{
  if (FUSS.distanceRead() < 10 && FUSS.distanceRead() > 0)
  //Serial.println("obstacle is near");
  return true;
  else 
  //Serial.println("no obstacle ahead");
  return false;
}

bool isRUSSnear()
{
   if (RUSS.distanceRead() < 10 && RUSS.distanceRead() > 0)
  //Serial.println("obstacle is near");
  return true;
  else 
  //Serial.println("no obstacle ahead");
  return false;
}

bool isLUSSnear()
{
  if (LUSS.distanceRead() < 10 && LUSS.distanceRead() > 0)
  //Serial.println("obstacle is near");
  return true;
  else 
  //Serial.println("no obstacle ahead");
  return false; 
}

void moveF(){
  analogWrite(in1,200);
  analogWrite(in2,0);
  analogWrite(in3,200);
  analogWrite(in4,0);
}
void moveB(){
  analogWrite(in1,0);
  analogWrite(in2,200);
  analogWrite(in3,0);
  analogWrite(in4,200);
}
 void moveR(){
  analogWrite(in1,200);
  analogWrite(in2,0);
  analogWrite(in3,0);
  analogWrite(in4,200);
 }
  void moveL(){
    analogWrite(in1,0);
    analogWrite(in2,200);
    analogWrite(in3,200);
    analogWrite(in4,0);
  }
void Stop()  {
  analogWrite(in1,0);
  analogWrite(in2,0);
  analogWrite(in3,0);
  analogWrite(in4,0);
  
}
void lefwerga3()
{
  moveR();
  moveR();
}
void turn(int x)
{
   if (x==6)
   moveR();
   else if( x==4)
   moveL();
   else
   Stop();
   
}
void swap(int x, int y){
  int z;
   z=x;
   x=y;
   y=z;
  R=x; L=y;
}

