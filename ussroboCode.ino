#include <Ultrasonic.h>

/*
 * ex.: Ultrasonic ultrasonic1 (trigpin, echopin)
 */
 
Ultrasonic FUSS(12, 11);
Ultrasonic RUSS(4, 2);
Ultrasonic LUSS(13, 7);

int choice = 4;                       //choice to turn either left or right, 4 represents left and 6 represents right.
int in1 = 3;
int in2 = 5;
int in3 = 6;
int in4 = 9;
int input=0;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  while (!isFUSSnear())
  {
    moveF();
    Serial.println("robot is walking forward ");
  }  
  
    if (isRUSSnear() && !isLUSSnear)
    {
     moveL();
     Serial.println("robot is turning left ");
    }
    
    else if(!isRUSSnear() && isLUSSnear())      
    {
      moveR();
      Serial.println("robot is turning right ");
      //Serial.print(L);
    }
    
    else if(isRUSSnear() && isLUSSnear())
    {
       Serial.println("robot is bylef w yerga3 ");
       swap(choice);  
    }

    else if(!isRUSSnear() && !isLUSSnear())
    {
      turn(choice);
      Serial.println("robot is turning ");
      Serial.print(choice);
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

void moveF()
{
  analogWrite(in1,200);
  analogWrite(in2,0);
  analogWrite(in3,200);
  analogWrite(in4,0);
}

void moveB()
{
  analogWrite(in1,0);
  analogWrite(in2,200);
  analogWrite(in3,0);
  analogWrite(in4,200);
}

void moveR()
{
  analogWrite(in1,200);
  analogWrite(in2,0);
  analogWrite(in3,0);
  analogWrite(in4,200);
}
 
  void moveL()
{
    analogWrite(in1,0);
    analogWrite(in2,200);
    analogWrite(in3,200);
    analogWrite(in4,0); 
}
  
void Stop()  
{
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
   if (x == 6)
    moveR();
   else if( x == 4)
    moveL();
   else
    Stop();
   
}

void swap(int x)
{
  if(x == 4)
   choice = 6;
  else if (x==6)
   choice = 4;
}

