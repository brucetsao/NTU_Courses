#include <String.h>
#include <Servo.h> 
/* Input for motorA:
   IN1      IN2      Action
   LOW      LOW      Motor Stop
   HIGH     LOW      Motor moves forward  
   LOW      HIGH     Motor moves backward
   HIGH     HIGH     Motor Stop
*/   
const int IN1Pin  = 11;
const int IN2Pin = 10;
const int IN3Pin = 9;      
const int IN4Pin = 8;       

const int DELAY = 3000;
#define TXPin 3
#define RXPin 2

#define Servo1Pin 12
#define Servo2Pin 13

#define EchoPin  5           
#define TrigPin  4          


#include <SoftwareSerial.h>   // 引用程式庫

// 定義連接藍牙模組的序列埠
SoftwareSerial BT(RXPin, TXPin); // 接收腳, 傳送腳
char val;  // 儲存接收資料的變數
//String CarCommand = String("FBLR") ;    //設定車子可以接受字串
String CarCommand = "FBLRX" ;    //設定車子可以接受字串
Servo myservo1;
Servo myservo2;

void setup()  
{
  pinMode(IN1Pin, OUTPUT);
  pinMode(IN2Pin, OUTPUT);
  pinMode(IN3Pin, OUTPUT);
  pinMode(IN4Pin, OUTPUT);  
//----------Servo
  myservo1.attach(Servo1Pin);
  myservo2.attach(Servo2Pin);

  //-------------HC-SR04  
    pinMode(EchoPin, INPUT);                   
    pinMode(TrigPin, OUTPUT);                 

  //------------BT_Talk Code

     Serial.begin(9600);   // 與電腦序列埠連線
  Serial.println("BT is ready!");

  // 設定藍牙模組的連線速率
  // 如果是HC-05，請改成9600
    BT.begin(9600);

  
}

void loop()
{
    if (BT.available()) 
    {
          val = BT.read();
          Serial.print(val);
        //    Serial.println(CarCommand.indexOf(2),DEC) ;
        //    Serial.println(CarCommand.indexOf('L'),DEC) ;
        //    Serial.println(CarCommand.indexOf('K'),DEC) ;
    if (CarCommand.indexOf(val) >0)
        {
          //  Serial.println(CarCommand.charAt(val)) ;
             BTCMD(val) ;     //執行車子命令

        }
    }
}
void BTCMD(char cmd)
{
    //執行車子命令

    if (cmd == 'F')
            forward();      //前進
    if (cmd == 'B')
            backward();     //向左
    if (cmd == 'L')
            left();         //向左
    if (cmd == 'R')
            right();        //向右
    if (cmd == 'X')
            motorstop();    //停車
      Serial.println(cmd) ;
  
}

double HC04_ultrasonic()
{
   double tmp = 0 ;
  double duration, distance;
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(TrigPin, LOW);
  duration = pulseIn(EchoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance >= 200 || distance <= 0){
    tmp = -1 ;
    Serial.print(distance);
    Serial.println(" cm");
    Serial.println("Out of range");
    Serial.println("--------------");
  }
  else {
        tmp = distance ;
    Serial.print(distance);
    Serial.println(" cm");
    Serial.println("read ok...");
    Serial.println("--------------");
  }
 
  return (tmp);
}


void Servo1Action(int angle)
{
    myservo1.write(angle);  // set servo to mid-poin
}

void Servo2Action(int angle)
{
    myservo2.write(angle);  // set servo to mid-poin
}



void selfTest()
{
  forward();
  delay(DELAY);
  motorstop(); delay(500);
  
  backward();
  delay(DELAY);
  motorstop(); delay(500);
  
  right();
  delay(DELAY);
  motorstop(); delay(500);
  
  left();
  delay(DELAY);
  motorstop(); delay(500);  
}

void motorstop()
{
  digitalWrite(IN1Pin, LOW);
  digitalWrite(IN2Pin, LOW);
  digitalWrite(IN3Pin, LOW);
  digitalWrite(IN4Pin, LOW);
}

void forward()
{
  digitalWrite(IN1Pin, LOW);
  digitalWrite(IN2Pin, HIGH);
  digitalWrite(IN3Pin, LOW);
  digitalWrite(IN4Pin, HIGH);
}

void backward()
{
  digitalWrite(IN1Pin, HIGH);
  digitalWrite(IN2Pin, LOW);
  digitalWrite(IN3Pin, HIGH);
  digitalWrite(IN4Pin, LOW);
}

// Let right motor keep running, but stop left motor
void right()
{
  digitalWrite(IN1Pin, LOW);
  digitalWrite(IN2Pin, HIGH);
  digitalWrite(IN3Pin, LOW);
  digitalWrite(IN4Pin, LOW);
}

// Let left motor keep running, but stop right motor
void left()
{
  digitalWrite(IN1Pin, LOW);
  digitalWrite(IN2Pin, LOW);
  digitalWrite(IN3Pin, LOW);
  digitalWrite(IN4Pin, HIGH);
}
