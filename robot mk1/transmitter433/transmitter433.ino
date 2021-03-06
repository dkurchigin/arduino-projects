#include <VirtualWire.h>

#define LED_PIN 13

#define STOP_MOVING "cm40"
#define MOVE_FORWARD "cm41"
#define MOVE_BACK "cm42"
#define MOVE_LEFT "cm43"
#define MOVE_RIGHT "cm44"

#define FORWARD_BUTTON 7
#define BACK_BUTTON 8
#define LEFT_BUTTON 9
#define RIGHT_BUTTON 10

char *cont;
int message;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN,OUTPUT);
  pinMode(FORWARD_BUTTON, INPUT);
  pinMode(BACK_BUTTON, INPUT);
  pinMode(LEFT_BUTTON, INPUT);
  pinMode(RIGHT_BUTTON, INPUT);
  
  vw_set_ptt_inverted(true);
  vw_set_tx_pin(12);
  vw_setup(1000);
}

void loop() {
  digitalWrite(LED_PIN, LOW);
  if (Serial.available() > 0) {
    message = Serial.read();
    if (message == '0') {
      send_message(STOP_MOVING);
    } else if (message == '1') {
      send_message(MOVE_FORWARD);
    } else if (message == '2') {
      send_message(MOVE_BACK);
    } else if (message == '3') {
      send_message(MOVE_LEFT);
    } else if (message == '4') {
      send_message(MOVE_RIGHT);
    } 
  }

  boolean forwardUp = digitalRead(FORWARD_BUTTON);
  boolean backUp = digitalRead(BACK_BUTTON);
  boolean leftUp = digitalRead(LEFT_BUTTON);
  boolean rightUp = digitalRead(RIGHT_BUTTON);
  if (!forwardUp) {
    send_message(MOVE_FORWARD);
  } else if (!backUp) {
    send_message(MOVE_BACK);
  } else if (!leftUp) {
    send_message(MOVE_LEFT);
  } else if (!rightUp) {
    send_message(MOVE_RIGHT);
  }
}

void send_message(char *command) {
  char *message = command;
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx();
  Serial.println(command);
  digitalWrite(LED_PIN, HIGH);
}

