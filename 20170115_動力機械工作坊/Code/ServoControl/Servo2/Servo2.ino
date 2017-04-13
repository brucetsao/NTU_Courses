#include <Servo.h> 

#define Servo1Pin 11
#define Servo2Pin 12

Servo myservo1;
Servo myservo2;
// lib declare
void InitServo(Servo myservo, int Pins) ;
void ServotoZero(Servo myservo) ;
void ServoMove(Servo myservo, int angle)  ;

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
      ServotoZero(myservo1) ;
      delay(2000) ;
      ServoMove(myservo1,0);
      delay(2000) ;
      ServotoZero(myservo1) ;
      delay(2000) ;
      ServoMove(myservo1,180);
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



