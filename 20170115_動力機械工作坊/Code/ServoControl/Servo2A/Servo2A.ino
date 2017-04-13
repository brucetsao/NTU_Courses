#include <Servo.h> 

#define Servo1Pin 11
#define Servo2Pin 12

Servo myservo1;
Servo myservo2;

void InitServo(Servo me, int Pins)
{
    me.attach(Pins) ;
}

void ServotoZero(Servo me)
{
    me.write(90) ;
}

void ServoMove(Servo me, int angle)
{
     me.write(angle) ;
}


void setup()  
{
//    init Serial echo  
     Serial.begin(9600);   // 與電腦序列埠連線
  Serial.println("Program  is ready!");
  
//----------Servo
    myservo1.attach(Servo1Pin) ;
    ServotoZero(myservo1) ;
    ServotoZero(myservo2) ;
   // myservo1.write(90) ;
    
}

void loop()
  {
      ServotoZero(myservo1) ;
//      myservo1.write(90)  ;
      delay(2000) ;
      ServoMove(myservo1,0) ;
//      myservo1.write(0) ;
      delay(2000) ;
      ServotoZero(myservo1) ;
//      myservo1.write(90)  ;
      delay(2000) ;
        ServoMove(myservo1,180) ;
//    myservo1.write(180) ;
      delay(2000) ;      
  }


