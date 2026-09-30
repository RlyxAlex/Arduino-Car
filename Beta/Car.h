#pragma once

#include <Arduino.h>
#include "pins.h"

static inline void motor(int dirpin1, int dirpin2, int speedpin, int speed) {
  digitalWrite(dirpin2, !digitalRead(dirpin1));

  if (speed == 0) {
    digitalWrite(dirpin1, LOW);
    analogWrite(speedpin, 0);
  }
  else if (speed > 0) {
    digitalWrite(dirpin1, LOW);
    analogWrite(speedpin, speed);
  }
  else {
    digitalWrite(dirpin1, HIGH);
    analogWrite(speedpin, -speed);
  }
}

//单轮控制
static inline void car_wheel_left(int speed) {
  motor(MOTOR_L_IN1, MOTOR_L_IN2, MOTOR_L_EN, speed);
}
static inline void car_wheel_right(int speed) {
  motor(MOTOR_R_IN1, MOTOR_R_IN2, MOTOR_R_EN, speed);
}

//两轮组合动作
static inline void car_drive(int left, int right) {
  car_wheel_left(left);
  car_wheel_right(right);
}

static inline void car_forward(int speed = 255)      { car_drive(speed,  speed); }
static inline void car_backward(int speed = 255)     { car_drive(-speed, -speed); }
static inline void car_stop()                        { car_drive(0, 0); }

//两轮反转
static inline void car_pivot_left(int speed = 200)   { car_drive( speed, -speed); }
static inline void car_pivot_right(int speed = 200)  { car_drive(-speed,  speed); }

// 弧线转向
static inline void car_arc_left(int speed = 150)     { car_drive( speed, 0); }
static inline void car_arc_right(int speed = 150)    { car_drive(0,  speed); }

static inline void car_setup() {
  pinMode(MOTOR_L_IN1, OUTPUT);
  pinMode(MOTOR_L_IN2, OUTPUT);
  pinMode(MOTOR_L_EN,  OUTPUT);
  pinMode(MOTOR_R_IN1, OUTPUT);
  pinMode(MOTOR_R_IN2, OUTPUT);
  pinMode(MOTOR_R_EN,  OUTPUT);

  car_stop();
}

//引脚初始化
static inline void Pin_setup() {
  pinMode(MOTOR_L_IN1, OUTPUT);
  pinMode(MOTOR_L_IN2, OUTPUT);
  digitalWrite(MOTOR_L_IN1, LOW);
  digitalWrite(MOTOR_L_IN2, LOW);
  pinMode(MOTOR_R_IN1, OUTPUT);
  pinMode(MOTOR_R_IN2, OUTPUT);
  digitalWrite(MOTOR_R_IN1, LOW);
  digitalWrite(MOTOR_R_IN2, LOW);
  pinMode(ULTRA_TRIG_Front, OUTPUT);
  pinMode(ULTRA_ECHO_Front, INPUT);
}