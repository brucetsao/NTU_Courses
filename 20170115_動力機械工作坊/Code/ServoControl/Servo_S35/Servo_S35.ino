#include <Servo.h> 

#define Servo1Pin 11
#define Servo2Pin 12

Servo myservo1;
Servo myservo2;
// lib declare
void InitServo(Servo myservo, int Pins) ;
void ServotoZero(Servo myservo) ;
void ServoMove(Servo myservo, int angle)  ;
void ServoForward(Servo myservo, unsigned int angle)  ;
void ServoBackward(Servo myservo, unsigned int angle) ;
void ServoStop(Servo myservo) ;

//main

void setup()  
{
//    init Serial echo  
     Serial.begin(9600);   // 與電腦序列埠連線
  Serial.println("Program  is ready!");
  
//----------Servo
//----------Servo
    myservo1.attach(Servo1Pin) ;
    myservo2.attach(Servo2Pin) ;    ServotoZero(myservo1) ;
    ServotoZero(myservo1) ;
    ServotoZero(myservo2) ;
    
}

void loop()
  {
      ServoStop(myservo1) ;
      delay(2000) ;
      ServoForward(myservo1,90);
      delay(2000) ;
      ServoStop(myservo1) ;
      delay(2000) ;
      ServoBackward(myservo1,30);
      delay(2000) ;      
  }



// following is user defined function

void InitServo(Servo myservo, int Pins)
{
    myservo.attach(Pins) ;
}

void ServotoZero(Servo myservo)
{
    myservo.write(90) ;
}

void ServoMove(Servo myservo, int angle)
{
    myservo.write(angle) ;
}

void ServoForward(Servo myservo, unsigned int angle)
{
    if (angle == 0)
          {
            ServotoZero(myservo) ;
          }
          else if (angle >0)
            {
              myservo.write(90+map(angle,1,100,1,90)) ;
            }    
}

void ServoBackward(Servo myservo, unsigned int angle)
{
    if (angle == 0)
          {
            ServotoZero(myservo) ;
          }
          else if (angle >0)
            {
              myservo.write(90-map(angle,1,100,1,90)) ;
            }    
}

void ServoStop(Servo myservo)
{
    ServotoZero(myservo) ;
}


