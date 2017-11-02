// Code Example for jolliFactory 2X Bi-color LED Matrix Pong Game Single Player example 1.0

/* Wirings

SPI connections between Arduino Nano/UNO and the 2X Bi-color LED Matrix Driver Modules are MOSI (Pin 11), SCK (Pin 13) and SS (Pin 10) at the Arduino side and Din, CLK and Load pins at the LED Matrix Driver Module respectively.        
8 ohms 0.5W speaker is connected via a 100 ohms resistor to Arduino Digital Pin 8 and Gnd


Rotary Encoder with built in RED/GREEN LED and built-in Push Button connected for game control:

Rotary Encoder  |  Arduino Nano  |  Remarks
_________________________________________________________
Terminal A      |  Pin 2         |  Encoder A Signal
Terminal C      |  GND           |  GND
Terminal B      |  Pin 3         |  Encoder B Signal
Terminal 1      |  GND           |  GND
Terminal 2      |  Pin 6         |  GREEN LED
Terminal 3      |  Pin 7         |  RED LED
Terminal 4      |  Pin 5         |  Push-Button


Please visit instructable at http://www.instructables.com/id/Arduino-based-Bi-color-LED-Matrix-Tetris-Game/ for more detail

*/




/* ============================= LED Matrix Display ============================= */
#include <SPI.h>          
       
#define GREEN 0                          
#define RED 1                            

#define offREDoffGREEN 0
#define offREDonGREEN 1
#define onREDoffGREEN 2

#define ISR_FREQ 190     //190=650Hz    // Sets the speed of the ISR

int SPI_CS = 10;// This SPI Chip Select pin controls the MAX7219
int bi_maxInUse = 2; //1; //No. of Bi-color LED Matrix used. This sketch is coded for use on either 1 or 2 LED Matrix long game
int maxInShutdown=RED; // indicates which LED Matrix color is currently off
int SetbrightnessValue = 15;
int colorMode = '3';  // default color (1 = RED, 2 = GREEN, 3 = ORANGE, 4 = blank off)

char msg[255] = " Game of Pong   * Powered By jolliFactory * ";
int msgsize = strlen(msg);


// The character set courtesy of cosmicvoid.

byte Font8x5[104*8] =
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
 0x02, 0x02, 0x02, 0x02, 0x02, 0x00, 0x02, 0x00,
 0x05, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x0A, 0x0A, 0x1F, 0x0A, 0x1F, 0x0A, 0x0A, 0x00,
 0x0E, 0x15, 0x05, 0x0E, 0x14, 0x15, 0x0E, 0x00,
 0x13, 0x13, 0x08, 0x04, 0x02, 0x19, 0x19, 0x00,
 0x06, 0x09, 0x05, 0x02, 0x15, 0x09, 0x16, 0x00,
 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x04, 0x02, 0x01, 0x01, 0x01, 0x02, 0x04, 0x00,
 0x01, 0x02, 0x04, 0x04, 0x04, 0x02, 0x01, 0x00,
 0x00, 0x0A, 0x15, 0x0E, 0x15, 0x0A, 0x00, 0x00,
 0x00, 0x04, 0x04, 0x1F, 0x04, 0x04, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x01,
 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
 0x10, 0x10, 0x08, 0x04, 0x02, 0x01, 0x01, 0x00,
 0x0E, 0x11, 0x19, 0x15, 0x13, 0x11, 0x0E, 0x00,
 0x04, 0x06, 0x04, 0x04, 0x04, 0x04, 0x0E, 0x00,
 0x0E, 0x11, 0x10, 0x0C, 0x02, 0x01, 0x1F, 0x00,
 0x0E, 0x11, 0x10, 0x0C, 0x10, 0x11, 0x0E, 0x00,
 0x08, 0x0C, 0x0A, 0x09, 0x1F, 0x08, 0x08, 0x00,
 0x1F, 0x01, 0x01, 0x0E, 0x10, 0x11, 0x0E, 0x00,
 0x0C, 0x02, 0x01, 0x0F, 0x11, 0x11, 0x0E, 0x00,
 0x1F, 0x10, 0x08, 0x04, 0x02, 0x02, 0x02, 0x00,
 0x0E, 0x11, 0x11, 0x0E, 0x11, 0x11, 0x0E, 0x00,
 0x0E, 0x11, 0x11, 0x1E, 0x10, 0x08, 0x06, 0x00,
 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x02, 0x00, 0x02, 0x02, 0x01,
 0x08, 0x04, 0x02, 0x01, 0x02, 0x04, 0x08, 0x00,
 0x00, 0x00, 0x0F, 0x00, 0x0F, 0x00, 0x00, 0x00,
 0x01, 0x02, 0x04, 0x08, 0x04, 0x02, 0x01, 0x00,
 0x0E, 0x11, 0x10, 0x08, 0x04, 0x00, 0x04, 0x00,
 0x0E, 0x11, 0x1D, 0x15, 0x0D, 0x01, 0x1E, 0x00,
 0x04, 0x0A, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x00,
 0x0F, 0x11, 0x11, 0x0F, 0x11, 0x11, 0x0F, 0x00,
 0x0E, 0x11, 0x01, 0x01, 0x01, 0x11, 0x0E, 0x00,
 0x07, 0x09, 0x11, 0x11, 0x11, 0x09, 0x07, 0x00,
 0x1F, 0x01, 0x01, 0x0F, 0x01, 0x01, 0x1F, 0x00,
 0x1F, 0x01, 0x01, 0x0F, 0x01, 0x01, 0x01, 0x00,
 0x0E, 0x11, 0x01, 0x0D, 0x11, 0x19, 0x16, 0x00,
 0x11, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11, 0x00,
 0x07, 0x02, 0x02, 0x02, 0x02, 0x02, 0x07, 0x00,
 0x1C, 0x08, 0x08, 0x08, 0x08, 0x09, 0x06, 0x00,
 0x11, 0x09, 0x05, 0x03, 0x05, 0x09, 0x11, 0x00,
 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x0F, 0x00,
 0x11, 0x1B, 0x15, 0x15, 0x11, 0x11, 0x11, 0x00,
 0x11, 0x13, 0x13, 0x15, 0x19, 0x19, 0x11, 0x00,
 0x0E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E, 0x00,
 0x0F, 0x11, 0x11, 0x0F, 0x01, 0x01, 0x01, 0x00,
 0x0E, 0x11, 0x11, 0x11, 0x15, 0x09, 0x16, 0x00,
 0x0F, 0x11, 0x11, 0x0F, 0x05, 0x09, 0x11, 0x00,
 0x0E, 0x11, 0x01, 0x0E, 0x10, 0x11, 0x0E, 0x00,
 0x1F, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00,
 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E, 0x00,
 0x11, 0x11, 0x11, 0x11, 0x0A, 0x0A, 0x04, 0x00,
 0x41, 0x41, 0x41, 0x49, 0x2A, 0x2A, 0x14, 0x00,
 0x11, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x11, 0x00,
 0x11, 0x11, 0x11, 0x0A, 0x04, 0x04, 0x04, 0x00,
 0x1F, 0x10, 0x08, 0x04, 0x02, 0x01, 0x1F, 0x00,
 0x07, 0x01, 0x01, 0x01, 0x01, 0x01, 0x07, 0x00,
 0x01, 0x01, 0x02, 0x04, 0x08, 0x10, 0x10, 0x00,
 0x07, 0x04, 0x04, 0x04, 0x04, 0x04, 0x07, 0x00,
 0x00, 0x04, 0x0A, 0x11, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00,
 0x01, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x06, 0x08, 0x0E, 0x09, 0x0E, 0x00,
 0x01, 0x01, 0x0D, 0x13, 0x11, 0x13, 0x0D, 0x00,
 0x00, 0x00, 0x06, 0x09, 0x01, 0x09, 0x06, 0x00,
 0x10, 0x10, 0x16, 0x19, 0x11, 0x19, 0x16, 0x00,
 0x00, 0x00, 0x06, 0x09, 0x07, 0x01, 0x0E, 0x00,
 0x04, 0x0A, 0x02, 0x07, 0x02, 0x02, 0x02, 0x00,
 0x00, 0x00, 0x06, 0x09, 0x09, 0x06, 0x08, 0x07,
 0x01, 0x01, 0x0D, 0x13, 0x11, 0x11, 0x11, 0x00,
 0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x02, 0x00,
 0x04, 0x00, 0x06, 0x04, 0x04, 0x04, 0x04, 0x03,
 0x01, 0x01, 0x09, 0x05, 0x03, 0x05, 0x09, 0x00,
 0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00,
 0x00, 0x00, 0x15, 0x2B, 0x29, 0x29, 0x29, 0x00,
 0x00, 0x00, 0x0D, 0x13, 0x11, 0x11, 0x11, 0x00,
 0x00, 0x00, 0x06, 0x09, 0x09, 0x09, 0x06, 0x00,
 0x00, 0x00, 0x0D, 0x13, 0x13, 0x0D, 0x01, 0x01,
 0x00, 0x00, 0x16, 0x19, 0x19, 0x16, 0x10, 0x10,
 0x00, 0x00, 0x0D, 0x13, 0x01, 0x01, 0x01, 0x00,
 0x00, 0x00, 0x0E, 0x01, 0x06, 0x08, 0x07, 0x00,
 0x00, 0x02, 0x07, 0x02, 0x02, 0x02, 0x04, 0x00,
 0x00, 0x00, 0x11, 0x11, 0x11, 0x19, 0x16, 0x00,
 0x00, 0x00, 0x11, 0x11, 0x11, 0x0A, 0x04, 0x00,
 0x00, 0x00, 0x11, 0x11, 0x15, 0x15, 0x0A, 0x00,
 0x00, 0x00, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x00,
 0x00, 0x00, 0x09, 0x09, 0x09, 0x0E, 0x08, 0x06,
 0x00, 0x00, 0x0F, 0x08, 0x06, 0x01, 0x0F, 0x00,
 0x04, 0x02, 0x02, 0x01, 0x02, 0x02, 0x04, 0x00,
 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00,
 0x01, 0x02, 0x02, 0x04, 0x02, 0x02, 0x01, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x1C, 0x2A, 0x49, 0x49, 0x41, 0x22, 0x1C, 0x00,
 0x1C, 0x22, 0x51, 0x49, 0x41, 0x22, 0x1C, 0x00,
 0x1C, 0x22, 0x41, 0x79, 0x41, 0x22, 0x1C, 0x00,
 0x1C, 0x22, 0x41, 0x49, 0x51, 0x22, 0x1C, 0x00,
 0x1C, 0x22, 0x41, 0x49, 0x49, 0x2A, 0x1C, 0x00,
 0x1C, 0x22, 0x41, 0x49, 0x45, 0x22, 0x1C, 0x00,
 0x1C, 0x22, 0x41, 0x4F, 0x41, 0x22, 0x1C, 0x00,
 0x1C, 0x22, 0x45, 0x49, 0x41, 0x22, 0x1C, 0x00};


byte lentbl_S[104] =
{
 2, 2, 3, 5, 5, 5, 5, 2, 
 3, 3, 5, 5, 2, 5, 1, 5, 
 5, 4, 5, 5, 5, 5, 5, 5, 
 5, 5, 1, 2, 4, 4, 4, 5, 
 5, 5, 5, 5, 5, 5, 5, 5, 
 5, 3, 5, 5, 4, 5, 5, 5, 
 5, 5, 5, 5, 5, 5, 5, 7, 
 5, 5, 5, 3, 5, 3, 5, 5, 
 2, 4, 5, 4, 5, 4, 4, 4, 
 5, 2, 3, 4, 2, 6, 5, 4, 
 5, 5, 5, 4, 3, 5, 5, 5, 
 5, 4, 4, 3, 2, 3, 0, 0, 
 7, 7, 7, 7, 7, 7, 7, 7
};

int curcharix = 0;
int curcharbit = 0;
int curcharixsave = 0;
int curcharbitsave = 0;
int curcharixsave2 = 0;
int curcharbitsave2 = 0;
char curchar;



/* ============================= Audio ============================= */
int speakerOut = 8;

#define mC 1911
#define mC1 1804
#define mD 1703
#define mEb 1607
#define mE 1517
#define mF 1432
#define mF1 1352
#define mG 1276
#define mAb 1204
#define mA 1136
#define mBb 1073
#define mB 1012
#define mc 955
#define mc1 902
#define md 851
#define meb 803
#define me 758
#define mf 716
#define mf1 676
#define mg 638
#define mab 602
#define ma 568
#define mbb 536
#define mb 506

#define mp 0  //pause


// MELODY and TIMING  =======================================
//  melody[] is an array of notes, accompanied by beats[],
//  which sets each note's relative length (higher #, longer note)
int melody[] = {mg};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int beats[]  = {4};

int MAX_COUNT = sizeof(melody) / sizeof(int); // Melody length, for looping.

// Set overall tempo
long tempo = 20000;
// Set length of pause between notes
int pause = 1000;
// Loop variable to increase Rest length
int rest_count = 100; //<-BLETCHEROUS HACK; See NOTES

// Initialize core variables
int tone_ = 0;
int beat = 0;
long duration  = 0;




/* ========================== Pong Game ========================= */
//int column = 1, row = random(8)+1;  // Seems like causing first few screens not showing red ball
int column = 1, row = random(bi_maxInUse*8 - 3)+1;   // 3 is the number of LED dots used for paddle
int directionX = 1, directionY = 1;
int paddle1Val = bi_maxInUse * 8 / 2 - 2;  // Place paddle around middle
int lastpaddle1Val = 99;

int initialSpeed = 200;
int speed = initialSpeed;
int counter = 0, mult = 10;

byte paddlePosition = 0XE0;
byte ballRowPosition = 0X80;
byte paddleCurrentPosition, ballCurrentRowPosition;

unsigned long startTime;
unsigned long elapsedTime;
int cnt = 0;
int ledState = LOW;

boolean gameReplay = false;
boolean triggerSound = false;

int score = 0;




/* ========================== Rotary Encoder ========================= */
//Rotary encoder for game control of paddle
//Rotary encoder code from article: http://bildr.org/2012/08/rotary-encoder-arduino/

int encoderPin1 = 2;
int encoderPin2 = 3;

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;

//Button on rotarty encoder
int encoderButtonPin = 5;

//LEDs on rotarty encoder
int encoderGreenLEDPin = 6;
int encoderRedLEDPin = 7;




//**********************************************************************************************************************************************************  
void setup()
{
  pinMode(SPI_CS, OUTPUT);
  pinMode(speakerOut, OUTPUT); 
  
  //Rotary encoder for paddle
  pinMode(encoderPin1, INPUT_PULLUP);  //turn pullup resistor on
  pinMode(encoderPin2, INPUT_PULLUP);  //turn pullup resistor on

  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
  attachInterrupt(0, updateEncoder, CHANGE); 
  attachInterrupt(1, updateEncoder, CHANGE);

  //Rotary encoder button SW
  pinMode(encoderButtonPin, INPUT_PULLUP); 
  
  //Rotary encoder LEDs  
  pinMode(encoderGreenLEDPin, OUTPUT);
  pinMode(encoderRedLEDPin, OUTPUT);
  
  TriggerSound();

  Serial.begin (9600);
  Serial.println("jolliFactory 2X Bi-color LED Matrix Pong Game Single Player example 1.0");              

  SPI.begin(); //setup SPI Interface

  bi_maxTransferAll(0x0F, 0x00);   // 00 - Turn off Test mode
  bi_maxTransferAll(0x09, 0x00);   //Register 09 - BCD Decoding  // 0 = No decoding
  bi_maxTransferAll(0x0B, 0x07);   //Register B - Scan limit 1-7  // 7 = All LEDS
  bi_maxTransferAll(0x0C, 0x01);   // 01 = on 00 = Power saving mode or shutdown

  setBrightness();
  
  randomSeed(analogRead(0));
  
  setISRtimer();                        // setup the timer
  startISR();                           // start the timer to toggle shutdown

  // Display scroll message. Start game if button depressed  
  while(digitalRead(encoderButtonPin) != LOW)
    displayMessage();
    
  encoderValue = bi_maxInUse * 8 / 2 - 2;  // Place paddle around middle
  paddle1Val = encoderValue;    
}




//**********************************************************************************************************************************************************  
void loop()
{
  // if the LED is off turn it on and vice-versa:
  if (ledState == LOW)
    ledState = HIGH;
  else
    ledState = LOW;

  // set the LED with the ledState of the variable:
  digitalWrite(encoderGreenLEDPin, ledState);  
  
  column += directionX;
  row += directionY;
  
  //************************ Ball hit paddle ******************************  
  if (column == 6 && directionX == 1 && (paddle1Val == row || paddle1Val+1 == row || paddle1Val+2 == row))
  {    
    if (directionY == 1 && (paddle1Val == row))
      directionY = 0;
    else if (directionY == -1 && (paddle1Val+2 == row))
      directionY = 0;
    else if (directionY == 0 && (paddle1Val == row))
      directionY = -1;
    else if (directionY == 0 && (paddle1Val+1 == row))
    {
      directionY = random(-1,1);  // Prevent player from playing 'sitting on the fence game'
      speed += 3;  // Bonus by slowing down the ball
    }
    else if (directionY == 0 && (paddle1Val+2 == row))
      directionY = 1;

    directionX = -1;
    triggerSound = true;
    
    score++;
  }
  
  //************************ Ball hit top edge ******************************  
  if (column == 0 && directionX == -1 )
  {   
    directionX = 1;
    triggerSound = true;
  }
  
  
  //************************ Ball hit extreme right edge ************************
  if (row == (bi_maxInUse*8-1) && directionY == 1 )
  //if (row == 7 && directionY == 1 ) {    //For 1 LED Matrix Game
  //if (row == 15 && directionY == 1 )     //For 2 LED Matrix Game
  {   
    directionY = -1;
    triggerSound = true;
  }
  
  //************************ Ball hit extreme left edge ************************  
  if (row == 0 && directionY == -1 )
  {   
    directionY = 1;
    triggerSound = true;
  }
  
  //************************ Ball hit bottom edge ******************************  
  if (column == 7) 
    oops();

  clearDisplay(RED);

  if (row < 8)  // Ball is within left LED matrix
  {
    ballCurrentRowPosition = ballRowPosition >> row;  // Shift right by the value in row
  } 
  else  // Ball is within right LED matrix
  {
    int temprow = row - 8;
    ballCurrentRowPosition = ballRowPosition >> temprow;  // Shift right by the value in temprow
  }

  
  if (row < 8 && bi_maxInUse > 1)  // Ball is within left LED matrix
  {
    bi_maxTransferSingle(RED, 2, column, ballCurrentRowPosition);  // Display RED ball in left LED Matrix 
  } 
  else  // Ball is within right LED matrix
  {
    bi_maxTransferSingle(RED, 1, column, ballCurrentRowPosition);  // Display RED ball in right LED Matrix 
  }
  
  
  if (triggerSound == true)
  {
    TriggerSound();
    triggerSound = false;
  }

  lastpaddle1Val = paddle1Val;

  clearDisplay(GREEN);

  if (paddle1Val < 8)  // LHS of Paddle is within left LED matrix
  {
    paddleCurrentPosition = paddlePosition >> paddle1Val;  // Shift right by the value in paddle1Val 
  }
  else  // LHS of Paddle is within right LED matrix
  {
    int temppaddle1Val = paddle1Val - 8;
    paddleCurrentPosition = paddlePosition >> temppaddle1Val;  // Shift right by the value in temppaddle1Val 
  }

  if (paddle1Val < 8 && bi_maxInUse > 1)
  {
    bi_maxTransferSingle(GREEN, 2, 7, paddleCurrentPosition); //For 2 LED Matrix Game   //Display GREEN paddle in left LED Matrix
  }
  else
  {
    bi_maxTransferSingle(GREEN, 1, 7, paddleCurrentPosition); //Display GREEN paddle in right LED Matrix
  }


  if (bi_maxInUse > 1)  //For 2 LED Matrix Game
  {
    if (paddle1Val == 6)
    {
      paddleCurrentPosition = 0X80;
      bi_maxTransferSingle(GREEN, 1, 7, paddleCurrentPosition); //For 2 LED Matrix Game    //Display part of GREEN paddle in right LED Matrix
    }
    else if (paddle1Val == 7)
    {
      paddleCurrentPosition = 0XC0;
      bi_maxTransferSingle(GREEN, 1, 7, paddleCurrentPosition); //For 2 LED Matrix Game    //Display part of GREEN paddle in right LED Matrix
    }
    else if (paddle1Val > 7)
    {
      bi_maxTransferSingle(GREEN, 1, 7, paddleCurrentPosition); //For 2 LED Matrix Game    //Display GREEN paddle in right LED Matrix
    }
  }

  if (!(counter % mult)) {speed -= 3; mult * mult;}
  
  if (speed < 20)  // Reduce game speed if high speed limit reached
    speed = initialSpeed / 2;
    
  delay(speed);
  counter++;
}




//**********************************************************************************************************************************************************  
void oops()
{  
  digitalWrite(encoderGreenLEDPin, LOW); 
  digitalWrite(encoderRedLEDPin, HIGH); 

  clearDisplay(RED);
  clearDisplay(GREEN);

  startTime = millis();       

  while(gameReplay==false)      //To re-play if any buttons depressed again
  {          
    for(int i=0;i<8;i++)
    {      
      elapsedTime = millis() - startTime;

      // Display random pattern for pre-defined period before blanking display
      if (elapsedTime < 2000)
      {            
        bi_maxTransferSingle(GREEN, 1, i, random(255));
        bi_maxTransferSingle(GREEN, 2, i, random(255));

        bi_maxTransferSingle(RED, 1, i,  random(255));
        bi_maxTransferSingle(RED, 2, i,  random(255));

        cnt = cnt + 1;
          
        if (cnt > 80)
        {
          TriggerSound();
          TriggerSound();
          cnt = 0;
        }
      }   
      else
      {
        // to pause game if Oops. Will resume if encoder button depressed again   
        int encoderButtonState = digitalRead(encoderButtonPin);

        if (encoderButtonState == LOW)
          gameReplay = true;          
 
        InttoMsg(score);
        
        displayMessage();  
      }  
    }     
  }
  // End of While


  gameReplay = false;  
  digitalWrite(encoderRedLEDPin, LOW);
  
  counter=0;
  speed=initialSpeed;
  column=1;
  
  score = 0;

  encoderValue = bi_maxInUse * 8 / 2 - 2;  // Place paddle around middle
  paddle1Val = encoderValue;
  
  //row = random(5)+1;    //For 1 LED Matrix Game
  //row = random(13)+1;    //For 2 LED Matrix Game
  row = random(bi_maxInUse*8 - 3)+1;    
}




//**********************************************************************************************************************************************************    
void displayMessage()  
{
  int i,j,k;
     
    curcharixsave2 = curcharix;
    curcharbitsave2 = curcharbit;

    for (i=15;i>=0;i=i-2) // Loop through our 8 Bi-color LED Matrices though only 2 Bi-color LED Matrices connected to slow down the scrolling speed
    //for (i=7;i>=0;i=i-2) // Loop through our 4 Bi-color LED Matrices 
    {
      delay(5);  // to further slow down scrolling speed

      for (j=0;j<8;j++) // Set up rows on current display
      {   
        byte outputbyte = 0;
   
        curchar = msg[curcharix];
        curcharixsave = curcharix;
        curcharbitsave = curcharbit; 
   
        for (k=7;k>=0;k--) // Copy over data for 8 columns to current row and send it to current display  - scroll from right to left
        {                                  
          byte currentcharbits;

          // This byte is the bitmap of the current character for the current row
          currentcharbits = Font8x5[((curchar-32)*8)+j];
  
          if (currentcharbits & (1<<curcharbit))
          outputbyte |= (1<<k);
   
          // advance the current character bit of current character
          curcharbit ++;
 
          if (curcharbit > lentbl_S[curchar-32]) // we are past the end of this character, so advance.
          {
            curcharbit = 0;
            curcharix += 1;  
            if (curcharix+1 > msgsize) curcharix=0;
            curchar = msg[curcharix];
          }
        }


        if (i<16)   //8 x Bi-color LED Matrix (need 16 x MAX7219)
        //if (i<8)   //4 x Bi-color LED Matrix (need 8 x MAX7219)
        {   
            bi_maxTransferOne((i+1)/2, j+1, outputbyte);              
        } 
        

        if (j != 7) // if this is not the last row, roll back advancement, if it is, leave the counters advanced.
        {
          curcharix = curcharixsave;
          curcharbit = curcharbitsave;
        } 
      }
    }
 
    curcharix = curcharixsave2;
    curcharbit = curcharbitsave2;   
 
    curchar = msg[curcharix];
 
 
    // advance the current character bit of current character   
    curcharbit ++;
    
    if (curcharbit > lentbl_S[curchar-32]) // we are past the end of this character, so advance.
    {
      curcharbit = 0;
      curcharix += 1;
      if (curcharix+1 > msgsize) curcharix=0;
      {
        curchar = msg[curcharix];
      }
    }  
        
    
}
  
  
  
 
//**********************************************************************************************************************************************************  
// Change Max72xx brightness
void setBrightness()
{    
  bi_maxTransferAll(0x0A, SetbrightnessValue);      //Set Brightness
  bi_maxTransferAll(0x00, 0x00);  //No-op commands
}




//**********************************************************************************************************************************************************  
// Clear Display
void clearDisplay(uint8_t whichColor) //whichColor = 0 for GREEN, 1 for RED
{
  for (int y=0; y<8; y++) {
    bi_maxTransferSingle(whichColor, 1, y, 0);
    bi_maxTransferSingle(whichColor, 2, y, 0);
  } 
}




//**********************************************************************************************************************************************************  
void bi_maxTransferAll(uint8_t address, uint8_t value) 
{
  stopISR();
  digitalWrite(SPI_CS, LOW); 

  for ( int c=1; c<= bi_maxInUse*2;c++) 
  {
    SPI.transfer(address);  // specify register
    SPI.transfer(value);  // put data
  }

  digitalWrite(SPI_CS, HIGH); 
  startISR();
}




//**********************************************************************************************************************************************************  
/**
 * Transfers data to a MAX7219/MAX7221 register of a particular Bi-color LED Matrix module.
 *
 * @param whichMax The Max72xx to load data and value into
 * @param address The register to load data into
 * @param value Value to store in the register
 */

 
void bi_maxTransferOne(uint8_t whichMax, uint8_t address, uint8_t value) 
{
  byte noop_reg = 0x00;    //max7219 No op register
  byte noop_value = 0x00;  //value

  stopISR();
  digitalWrite(SPI_CS, LOW); 

  for (int i=bi_maxInUse; i>0; i--)   // Loop through our number of Bi-color LED Matrices 
  {
    if (i==whichMax)
    {
      SPI.transfer(address);  // Send the register address
      SPI.transfer(value);    // Send the value

      SPI.transfer(address);  // Send the register address
      SPI.transfer(value);    // Send the value
    }
    else
    {
      SPI.transfer(noop_reg);    // Send the register address
      SPI.transfer(noop_value);  // Send the value

      SPI.transfer(noop_reg);    // Send the register address
      SPI.transfer(noop_value);  // Send the value
    }
  }

  digitalWrite(SPI_CS, HIGH);
  startISR();
}




//**********************************************************************************************************************************************************  
void bi_maxTransferSingle(uint8_t whichColor, uint8_t whichMax, uint8_t address, uint8_t value)    //whichColor = 1 for RED, 2 for GREEN
{
  byte noop_reg = 0x00;    //max7219 No op register
  byte noop_value = 0x00;  //value

  stopISR();
  digitalWrite(SPI_CS, LOW); 


  if (whichColor==0)  // 0 = GREEN
  {
    for (int i=bi_maxInUse; i>0; i--)   // Loop through our number of Bi-color LED Matrices 
    {
      if (i==whichMax)
      {
        SPI.transfer(address+1);  // Send the register address
        SPI.transfer(value);    // Send the value

        SPI.transfer(noop_reg);  // Send the register address
        SPI.transfer(noop_value);    // Send the value
      }
      else
      {
        SPI.transfer(noop_reg);    // Send the register address
        SPI.transfer(noop_value);  // Send the value

        SPI.transfer(noop_reg);    // Send the register address
        SPI.transfer(noop_value);  // Send the value
      }
    }
  }
  else
  {
    for (int i=bi_maxInUse; i>0; i--)   // Loop through our number of Bi-color LED Matrices 
    {
      if (i==whichMax)
      {
        SPI.transfer(noop_reg);    // Send the register address
        SPI.transfer(noop_value);  // Send the value

        SPI.transfer(address+1);   // Send the register address
        SPI.transfer(value);       // Send the value
      }
      else
      {
        SPI.transfer(noop_reg);    // Send the register address
        SPI.transfer(noop_value);  // Send the value

        SPI.transfer(noop_reg);    // Send the register address
        SPI.transfer(noop_value);  // Send the value
      }
    }
  }

  digitalWrite(SPI_CS, HIGH);
  startISR();
}




//**********************************************************************************************************************************************************  
void bi_maxShutdown(uint8_t cmd) 
{
  byte noop_reg = 0x00;      //max7219_reg_no_op
  byte shutdown_reg = 0x0c;  //max7219_reg_shutdown
  byte col = 0x01;  //shutdown false
  byte col2 = 0x00;  //shutdown true


  if (cmd == offREDoffGREEN)
  {    
    stopISR();
    digitalWrite(SPI_CS, LOW);

    for (int c =1; c<= bi_maxInUse; c++)
    {
      SPI.transfer(shutdown_reg);  // Send the register address
      SPI.transfer(col2);          // Send the value

      SPI.transfer(shutdown_reg);  // Send the register address
      SPI.transfer(col2);          // Send the value
    }

    digitalWrite(SPI_CS, HIGH);    
    startISR();
  }
  else if (cmd == offREDonGREEN)
  {
    stopISR();
    digitalWrite(SPI_CS, LOW);

    for (int c =1; c<= bi_maxInUse; c++) 
    {
      SPI.transfer(shutdown_reg);  // Send the register address
      SPI.transfer(col);           // Send the value

      SPI.transfer(shutdown_reg);  // Send the register address
      SPI.transfer(col2);          // Send the value
    }

    digitalWrite(SPI_CS, HIGH);
    startISR();
  }
  else if (cmd == onREDoffGREEN)
  {
    stopISR();
    digitalWrite(SPI_CS, LOW);

    for (int c =1; c<= bi_maxInUse; c++) 
    {      
      SPI.transfer(shutdown_reg);  // Send the register address
      SPI.transfer(col2);          // Send the value

      SPI.transfer(shutdown_reg);  // Send the register address
      SPI.transfer(col);           // Send the value  
    }

    digitalWrite(SPI_CS, HIGH);
    startISR();
  }

  //No ops register to shift out instructions   
  stopISR();
  digitalWrite(SPI_CS, LOW);

  for (int c =1; c<= bi_maxInUse; c++) 
  {      
    SPI.transfer(noop_reg);  // Send the register address
    SPI.transfer(0x00);      // Send the value

    SPI.transfer(noop_reg);  // Send the register address
    SPI.transfer(0x00);      // Send the value
  }

  digitalWrite(SPI_CS, HIGH);
  startISR();
}




//**********************************************************************************************************************************************************
ISR(TIMER2_COMPA_vect) {  //This ISR toggles shutdown between the 2MAX7221's

  if (colorMode == '3')    //ORANGE
  {
    if(maxInShutdown==RED){
      bi_maxShutdown(onREDoffGREEN);
      maxInShutdown=GREEN;
    } 
    else 
    { 
      bi_maxShutdown(offREDonGREEN);
      maxInShutdown=RED;
    }
  }
  else if (colorMode == '2')   //GREEN
  {
    bi_maxShutdown(offREDonGREEN);
    maxInShutdown=RED;
  }
  else if (colorMode == '1')   //RED
  {
    bi_maxShutdown(onREDoffGREEN);
    maxInShutdown=GREEN;
  }
  else if (colorMode == '4')  //Blank Display
  {
    bi_maxShutdown(offREDoffGREEN);       
    maxInShutdown=GREEN;
  }
} 




// Timer 2 - Used for alternate shutdown of MAX7219 for Arduino pro mini, UNO, Nano
//**********************************************************************************************************************************************************
void setISRtimer(){ 
  TCCR2A = 0x02;                        // WGM22=0 + WGM21=1 + WGM20=0 = Mode2 (CTC)
  TCCR2B = 0x05;                        // CS22=1 + CS21=0 + CS20=1 = /128 prescaler (125kHz)
  TCNT2 = 0;                            // clear counter
  OCR2A = ISR_FREQ;                     // set TOP (divisor) - see #define
}
     


     
//**********************************************************************************************************************************************************
void startISR(){  // Starts the ISR
  TCNT2 = 0;                            // clear counter (needed here also)
  TIMSK2|=(1<<OCIE2A);                  // set interrupts=enabled (calls ISR(TIMER2_COMPA_vect)
}


  
     
//**********************************************************************************************************************************************************
void stopISR(){    // Stops the ISR
  TIMSK2&=~(1<<OCIE2A);                  // disable interrupts
}




//**********************************************************************************************************************************************************
void TriggerSound()
{
  // Set up a counter to pull from melody[] and beats[]
  for (int i=0; i<MAX_COUNT; i++) {
    tone_ = melody[i];
    beat = beats[i];

    duration = beat * tempo;

    playTone();
    delayMicroseconds(pause);
  }
}




//**********************************************************************************************************************************************************
// Pulse the speaker to play a tone for a particular duration
void playTone() 
{
  long elapsed_time = 0;
  if (tone_ > 0) { // if this isn't a Rest beat, while the tone has
    //  played less long than 'duration', pulse speaker HIGH and LOW
    while (elapsed_time < duration) {

      digitalWrite(speakerOut,HIGH);
      delayMicroseconds(tone_ / 2);

      // DOWN
      digitalWrite(speakerOut, LOW);
      delayMicroseconds(tone_ / 2);

      // Keep track of how long we pulsed
      elapsed_time += (tone_);
    }
  }
  else { // Rest beat; loop times delay
    for (int j = 0; j < rest_count; j++) { // See NOTE on rest_count
      delayMicroseconds(duration);  
    }                                
  }                                
}




//**********************************************************************************************************************************************************
void updateEncoder()
{
  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;

  lastEncoded = encoded; //store this value for next time  
  
  if (encoderValue < 0)
    encoderValue = 0;
/*
  else if (encoderValue > 13)
    encoderValue = 13;
    */
    
  else if (encoderValue > (bi_maxInUse*8 - 3))
    encoderValue = bi_maxInUse*8 - 3;
  
  paddle1Val = encoderValue; 
}




//**********************************************************************************************************************************************************
// Convert Int to char for display
void InttoMsg(int v) 
{ 
  int i = 0;
  String tempString = String(v);  

  int tempLength = tempString.length();

  char cstr[tempLength+1]; 
  tempString.toCharArray(cstr, tempLength+1);  

  msg[i++] = 'S';
  msg[i++] = 'c';
  msg[i++] = 'o';
  msg[i++] = 'r';
  msg[i++] = 'e';
  msg[i++] = ' ';


  for (int j=0; j<tempLength; j++){
    msg[i++]= cstr[j];
  }
  
  // Add number of spaces to end of string  
  for (int k=0; k<8; k++){
    msg[i++]=' ';       
  }

  msg[i++]='\0'; // Null terminate the string       
  
  msgsize = strlen(msg);
}    

