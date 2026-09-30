#include <Wire.h>
#include <LiquidCrystal_I2C.h>

enum BrakeSwitch : bool {
  Disable = false,
  Enabled = true
};

LiquidCrystal_I2C lcd_tail(0x27,16,2);

BrakeSwitch BrakeActivated = Enabled;

//Motor函数--dirpin1（第一个参数）:方向管脚1，dirpin2：方向管脚2，speedpin：EN管脚，speed：速度值（-255-255）
void Motor(int dirpin1,int dirpin2,int speedpin,int speed){
  digitalWrite(dirpin2,!digitalRead(dirpin1));
  if(speed == 0){
    digitalWrite(dirpin1,LOW);
    analogWrite(speedpin,0);
  }
  else if(speed > 0){
    digitalWrite(dirpin1,LOW);
    analogWrite(speedpin,speed);
  }
  else{
    digitalWrite(dirpin1,HIGH);
    analogWrite(speedpin,-speed);
  }
}
//Ultrasound_front函数 ：超声波测距,Trig:13,Echo:12
float Ultrasound_front(){
  digitalWrite(13,LOW);
  delayMicroseconds(2);
  digitalWrite(13,HIGH);
  delayMicroseconds(10);
  digitalWrite(13,LOW);
  float distance = pulseIn(12,HIGH) / 58.00;
  delay(10);
  return distance;
}

void Display(){
  lcd_tail.clear();
  lcd_tail.setCursor(0, 0);
  lcd_tail.print(String(Ultrasound_front()) + String("cm"));
  delay(500);
}

void straight(){
  if (BrakeActivated==Disable) {
    Motor(5, 7, 6, 255);
    Motor(8, 10, 11, 255);
  }
  else{
    return;
  }
}

void Reversing(){
  if (BrakeActivated==Enabled) {
    Motor(5, 7, 6, -255);
    Motor(8, 10, 11, -255);
  }
}

void brake(){
  Motor(5, 7, 6, 0);
  Motor(8, 10, 11, 0);
}

void setup(){
  lcd_tail.init();
  lcd_tail.backlight();
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(5, LOW);
  digitalWrite(7, LOW);
  pinMode(8, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(8, LOW);
  digitalWrite(10, LOW);
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(12, INPUT);
  Motor(5, 7, 6, 0);
  Motor(8, 10, 11, 0);
}
void loop(){
  Display();
  Serial.flush();
  if(Ultrasound_front() <= 30){
    Display();
    brake();
    BrakeActivated=Enabled;
  }
  else{
    BrakeActivated=Disable;
  }
  straight();
}