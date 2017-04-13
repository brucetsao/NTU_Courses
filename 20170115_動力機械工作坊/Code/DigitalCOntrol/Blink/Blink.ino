
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);    //定義D13為輸出腳位
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(13, HIGH);   // 將腳位D13設定為高電位  turn the LED on (HIGH is the voltage level)
  delay(1000);              //休息1秒 wait for a second  
  digitalWrite(13, LOW);    // 將腳位D13設定為低電位  turn the LED off by making the voltage LOW
  delay(1000);              // 休息1秒 wait for a second
}
