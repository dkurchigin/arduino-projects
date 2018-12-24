#include <VirtualWire.h>
#include <ServoTimer2.h>

#define LED_PIN 13
#define TOP_RIGHT_MSFT A0
#define TOP_LEFT_MSFT A1
#define BOTTOM_RIGHT_MSFT A2
#define BOTTOM_LEFT_MSFT A3
#define RIGHT_SERVO 9
#define LEFT_SERVO 10

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
  pinMode(TOP_RIGHT_MSFT, OUTPUT);
  pinMode(TOP_LEFT_MSFT, OUTPUT);
  pinMode(BOTTOM_RIGHT_MSFT, OUTPUT);
  pinMode(BOTTOM_LEFT_MSFT, OUTPUT);
  analogWrite(TOP_RIGHT_MSFT, 0);
  analogWrite(TOP_LEFT_MSFT, 0);
  analogWrite(BOTTOM_RIGHT_MSFT, 0);
  analogWrite(BOTTOM_LEFT_MSFT, 0);
  moveRobot("all_back");
}

void loop() {
  moveRobot("forward");
  moveRobot("back");
  moveRobot("left");
  moveRobot("stop");
  moveRobot("right");
  moveRobot("stop");
  
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
    analogWrite(TOP_RIGHT_MSFT, 255);
    analogWrite(TOP_LEFT_MSFT, 0);
    analogWrite(BOTTOM_RIGHT_MSFT, 0);
    analogWrite(BOTTOM_LEFT_MSFT, 255);
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
    analogWrite(TOP_RIGHT_MSFT, 0);
    analogWrite(TOP_LEFT_MSFT, 255);
    analogWrite(BOTTOM_RIGHT_MSFT, 255);
    analogWrite(BOTTOM_LEFT_MSFT, 0);
    delay(300);
  }
  if (command == "stop") {
    analogWrite(TOP_RIGHT_MSFT, 0);
    analogWrite(TOP_LEFT_MSFT, 0);
    analogWrite(BOTTOM_RIGHT_MSFT, 0);
    analogWrite(BOTTOM_LEFT_MSFT, 0);
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
    analogWrite(TOP_RIGHT_MSFT, 255);
    analogWrite(TOP_LEFT_MSFT, 0);
    analogWrite(BOTTOM_RIGHT_MSFT, 0);
    analogWrite(BOTTOM_LEFT_MSFT, 255);
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
    analogWrite(TOP_RIGHT_MSFT, 255);
    analogWrite(TOP_LEFT_MSFT, 0);
    analogWrite(BOTTOM_RIGHT_MSFT, 0);
    analogWrite(BOTTOM_LEFT_MSFT, 255);
    delay(300);
  }
}
