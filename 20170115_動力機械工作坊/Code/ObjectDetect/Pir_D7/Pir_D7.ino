#define Pir_Pin 7
#define Led_Pin 8
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin Blink_Led_Pin as an output.
  pinMode(Led_Pin, OUTPUT);   //定義Blink_Led_Pin為輸出腳位
  pinMode(Pir_Pin, INPUT);   //定義Blink_Led_Pin為輸出腳位
}

// the loop function runs over and over again forever
void loop() {
     if (digitalRead(Pir_Pin))
        {
            digitalWrite(Led_Pin, HIGH);   // 將腳位Blink_Led_Pin設定為高電位  turn the LED on (HIGH is the voltage level)
        }
        else
        {
            digitalWrite(Led_Pin, LOW);   // 將腳位Blink_Led_Pin設定為高電位  turn the LED on (HIGH is the voltage level)
        }
        
  delay(1000);              //休息1秒 wait for a second  
}
