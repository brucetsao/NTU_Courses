
const int IN1Pin  = 7;
const int IN2Pin = 6;
const int IN3Pin = 5;      
const int IN4Pin = 4;       

const int DELAY = 3000;
// lib declare
void InitPins() ;
void MotorAllStop() ;  // Car Stop
void Forward()  ;  // Car forward
void Backward() ;
void RightWheelForward()  ;
void RightWheelBackward() ;
void RightWheelStop() ;
void LeftWheelForward() ;
void LeftWheelBackward()  ;
void LeftWheelStop()  ;
void TurnRight()  ;
void TurnLeft() ;
void BTCMD(char cmd)  ;
void selfTest() ;

//main
void setup()  
{
  InitPins() ;

  //------------init Serial Code

     Serial.begin(9600);   // 與電腦序列埠連線
  Serial.println("Program is ready!");

  selfTest() ;
}

void loop()
{
 
}


// following is user defined function

void InitPins()
{
    pinMode(IN1Pin, OUTPUT);
    pinMode(IN2Pin, OUTPUT);
     pinMode(IN3Pin, OUTPUT);
     pinMode(IN4Pin, OUTPUT); 
}
void MotorAllStop()
{
    RightWheelStop() ;
    LeftWheelStop() ;
}

void Forward()
{
  RightWheelForward() ;
  LeftWheelForward() ;
}

void Backward()
{
    RightWheelBackward() ;
    LeftWheelBackward() ;
}

// Let right motor keep running, but stop left motor



// Let left motor keep running, but stop right mo

void RightWheelForward()
{
  digitalWrite(IN1Pin, HIGH);
  digitalWrite(IN2Pin, LOW);
}

void RightWheelBackward()
{
  digitalWrite(IN1Pin, LOW);
  digitalWrite(IN2Pin, HIGH );
}
void RightWheelStop()
{
  digitalWrite(IN1Pin, LOW);
  digitalWrite(IN2Pin, LOW );
}

void LeftWheelForward()
{
  digitalWrite(IN3Pin, HIGH);
  digitalWrite(IN4Pin, LOW);
}

void LeftWheelBackward()
{
  digitalWrite(IN3Pin, LOW);
  digitalWrite(IN3Pin, HIGH );
}
void LeftWheelStop()
{
  digitalWrite(IN3Pin, LOW);
  digitalWrite(IN4Pin, LOW );
}
void TurnRight()
{
   RightWheelBackward() ;
   LeftWheelForward() ;
}   

void TurnLeft()
{
     RightWheelForward() ;
     LeftWheelBackward() ;
}
void BTCMD(char cmd)
{
    //執行車子命令

    if (cmd == 'F')
            Forward();      //前進
    if (cmd == 'B')
            Backward();     //向左
    if (cmd == 'L')
            TurnLeft();         //向左
    if (cmd == 'R')
            TurnRight();        //向右
    if (cmd == 'X')
            MotorAllStop();    //停車
   
      Serial.println(cmd) ;
  
}


void selfTest()
{
   BTCMD('X') ;
  delay(DELAY);
   BTCMD('F') ;
  delay(DELAY);
   BTCMD('B') ;
  delay(DELAY);
   BTCMD('L') ;
  delay(DELAY);
   BTCMD('R') ;
  delay(DELAY);
   BTCMD('X') ;
  delay(DELAY);
}



