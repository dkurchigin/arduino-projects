#include <VirtualWire.h>
#include <ServoTimer2.h>

#define LED_PIN 13
#define RIGHT_MSFTS A2
#define LEFT_MSFTS A1
#define RIGHT_SERVO 9
#define LEFT_SERVO 10
#define MOTOR_SPEED 150

int timer;
ServoTimer2 l_servo;
ServoTimer2 r_servo;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  vw_set_ptt_inverted(true); 
  vw_set_rx_pin(12);
  vw_setup(1000); 
  vw_rx_start(); 
  pinMode(RIGHT_MSFTS, OUTPUT);
  pinMode(LEFT_MSFTS, OUTPUT);
  analogWrite(RIGHT_MSFTS, 0);
  analogWrite(LEFT_MSFTS, 0);
  moveRobot("stop");
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  if (vw_get_message(buf, &buflen)) {  
    if (buf[0] == 'c' && buf[1] == 'm') {
      if (buf[2] == '4') {
        if (buf[3] == '0') {
          digitalWrite(LED_PIN,HIGH);
          moveRobot("back");
          delay(100);  
        } else if (buf[3] == '1') {
          digitalWrite(LED_PIN,HIGH);
          moveRobot("forward");
          delay(100);  
        } else if (buf[3] == '2') {
          digitalWrite(LED_PIN,HIGH);
          moveRobot("right");
          delay(100);
        } else if (buf[3] == '3') {
          digitalWrite(LED_PIN,HIGH);
          moveRobot("left");
          delay(100);
        }     
      }
    }
  } else {
    moveRobot("stop");
  }
}

void moveRobot(String command) {
  if (command == "forward") {
    l_servo.attach(LEFT_SERVO);
    r_servo.attach(RIGHT_SERVO);
    l_servo.write(900);/*have contact*/
    r_servo.write(1600);/*have contact*/
    delay(300);
    l_servo.detach();
    r_servo.detach();
    analogWrite(RIGHT_MSFTS, MOTOR_SPEED);
    analogWrite(LEFT_MSFTS, 0);
    delay(300);
  }
  if (command == "back") {
    l_servo.attach(LEFT_SERVO);
    r_servo.attach(RIGHT_SERVO);
    l_servo.write(900);/*have contact*/
    r_servo.write(1600);/*have contact*/
    delay(300);
    l_servo.detach();
    r_servo.detach();
    analogWrite(RIGHT_MSFTS, 0);
    analogWrite(LEFT_MSFTS, MOTOR_SPEED);
    delay(300);
  }
  if (command == "stop") {
    analogWrite(RIGHT_MSFTS, 0);
    analogWrite(LEFT_MSFTS, 0);
    l_servo.attach(LEFT_SERVO);
    r_servo.attach(RIGHT_SERVO);
    l_servo.write(1500);/*dont have contact*/
    r_servo.write(1000);/*dont have contact*/
    delay(300);
    l_servo.detach();
    r_servo.detach();
  }
  if (command == "left") {
    l_servo.attach(LEFT_SERVO);
    r_servo.attach(RIGHT_SERVO);
    l_servo.write(900);/*have contact*/
    r_servo.write(1000);/*dont have contact*/
    delay(300);
    l_servo.detach();
    r_servo.detach();
    analogWrite(RIGHT_MSFTS, MOTOR_SPEED);
    analogWrite(LEFT_MSFTS, 0);
    delay(300);
  }
  if (command == "right") {
    l_servo.attach(LEFT_SERVO);
    r_servo.attach(RIGHT_SERVO);
    l_servo.write(1500);/*dont have contact*/
    r_servo.write(1600);/*have contact*/
    delay(300);
    l_servo.detach();
    r_servo.detach();
    analogWrite(RIGHT_MSFTS, MOTOR_SPEED);
    analogWrite(LEFT_MSFTS, 0);
    delay(300);
  }
}
