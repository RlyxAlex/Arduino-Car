#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C mylcd(0x27,16,2);

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
//checkdistance_13_12函数 ：超声波测距,Trig:13,Echo:12
float checkdistance_13_12(){
  digitalWrite(13,LOW);
  delayMicroseconds(2);
  digitalWrite(13,HIGH);
  delayMicroseconds(10);
  digitalWrite(13,LOW);
  float distance = pulsIn(12,HIGH) / 58.00;
  delay(10);
  return distance;
}

void setup(){
  mylcd.init();
  mylcd.backlight();
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
  setMotor(5, 7, 6, 0);
  setMotor(8, 10, 9, 0);
  Serial.println("Serial is Ready");
  Serial.println("LCD is Ready");
  delay(250);
  Serial.println("Motor is Ready");
  delay(250);
  if (checkdistance_13_12() > 0) {
    Serial.println("Ultrasound Ready");
    delay(500);
  }
  Serial.println("Wifi Connecting");
  Serial.println("All Ready");
  delay(2000);
}
void loop(){

}