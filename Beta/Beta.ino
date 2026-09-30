#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Car.h"

enum BrakeSwitch : bool {
  Disable = false,
  Enabled = true
};

LiquidCrystal_I2C lcd_tail(0x27,16,2);

BrakeSwitch BrakeActivated = Enabled;

//Ultrasound_front函数 ：超声波测距,Trig:13,Echo:12
float Ultrasound_front(){
  digitalWrite(ULTRA_TRIG_Front,LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRA_TRIG_Front,HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRA_TRIG_Front,LOW);
  float distance = pulseIn(ULTRA_ECHO_Front,HIGH) / 58.00;
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
    car_forward(255);
  }
  else{
    return;
  }
}

void Reversing(){
  if (BrakeActivated==Enabled) {
    car_backward(255);
  }
}

void brake(){
  car_stop();
}

void setup(){
  lcd_tail.init();
  lcd_tail.backlight();
  Serial.begin(9600);
  Pin_setup();
  car_setup();
  car_stop();
}
void loop(){
  Display();
  Serial.flush();
  if(Ultrasound_front() <= 30){
    Display();
    brake();
    delay(1000);
    Reversing()
    BrakeActivated=Enabled;
  }
  else{
    BrakeActivated=Disable;
  }
  straight();
}