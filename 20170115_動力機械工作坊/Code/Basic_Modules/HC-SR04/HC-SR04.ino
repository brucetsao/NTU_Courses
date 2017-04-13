#define EchoPin  5           
#define TrigPin  4          
// Declare Lib
  ftgvoid InitPins()  ;jhn
  double HC04_ultrasonic() ;
  
// main

void setup()  
{

    InitPins() ;
    
  
}

void loop()
{
      Serial.print("Now Use Ultrasonic to Detect the object distance:(") ;
      Serial.print(HC04_ultrasonic()) ;
      Serial.println(") cm \n");
        delay(3000) ;
}


// user defined lib
  void InitPins() 
  {
      //-------------HC-SR04  
        pinMode(EchoPin, INPUT);                   
        pinMode(TrigPin, OUTPUT);                 

       //------------Serial Code

     Serial.begin(9600);   // 與電腦序列埠連線
  Serial.println("Program is ready!");

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


