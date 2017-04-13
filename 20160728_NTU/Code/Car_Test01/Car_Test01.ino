
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

void setup()  
{
  pinMode(IN1Pin, OUTPUT);
  pinMode(IN2Pin, OUTPUT);
  pinMode(IN3Pin, OUTPUT);
  pinMode(IN4Pin, OUTPUT);    
}

void loop()
{
  selfTest();
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
