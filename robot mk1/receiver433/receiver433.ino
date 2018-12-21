#include <VirtualWire.h>

#define LED_PIN 13
#define TOP_RIGHT_MSFT A0
#define TOP_LEFT_MSFT A1
#define BOTTOM_RIGHT_MSFT A2
#define BOTTOM_LEFT_MSFT A3

int timer;

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
  analogWrite(TOP_RIGHT_MSFT, 255);
  analogWrite(TOP_LEFT_MSFT, 255);
  analogWrite(BOTTOM_RIGHT_MSFT, 0);
  analogWrite(BOTTOM_LEFT_MSFT, 0);
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  if (vw_get_message(buf, &buflen)) {  
    if (buf[0] == 'c' && buf[1] == 'm') {
      if (buf[2] == '4') {
        if (buf[3] == '0') {
          digitalWrite(LED_PIN,HIGH);
          moveMotor("back");
          delay(100);  
        } else if (buf[3] == '1') {
          digitalWrite(LED_PIN,HIGH);
          moveMotor("forward");
          delay(100);  
        } else if (buf[3] == '2') {
          digitalWrite(LED_PIN,HIGH);
          moveMotor("forward");
          delay(100);
        } else if (buf[3] == '3') {
          digitalWrite(LED_PIN,HIGH);
          moveMotor("forward");
          delay(100);
        }     
      }
    }
  } else {
    moveMotor("stop");
  }
}

void moveMotor(String command) {
  if (command == "forward") {
    analogWrite(TOP_RIGHT_MSFT, 255);
    analogWrite(TOP_LEFT_MSFT, 0);
    analogWrite(BOTTOM_RIGHT_MSFT, 255);
    analogWrite(BOTTOM_LEFT_MSFT, 0);
  }
  if (command == "back") {
    analogWrite(TOP_RIGHT_MSFT, 0);
    analogWrite(TOP_LEFT_MSFT, 255);
    analogWrite(BOTTOM_RIGHT_MSFT, 0);
    analogWrite(BOTTOM_LEFT_MSFT, 255);
  }if (command == "stop") {
    analogWrite(TOP_RIGHT_MSFT, 255);
    analogWrite(TOP_LEFT_MSFT, 255);
    analogWrite(BOTTOM_RIGHT_MSFT, 0);
    analogWrite(BOTTOM_LEFT_MSFT, 0);
  }
}
