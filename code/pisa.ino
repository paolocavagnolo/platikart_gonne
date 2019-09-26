
#include <Controllino.h>

const byte interruptPin0 = CONTROLLINO_IN0;
const byte interruptPin1 = CONTROLLINO_IN1;

const byte runPin = CONTROLLINO_D1;
const byte velPin = CONTROLLINO_D2;
const byte ledPin = CONTROLLINO_D4;

volatile uint8_t i = 0;
volatile long iniA = 0;
volatile long iniB = 0;

void setup() {

  pinMode(interruptPin0, INPUT);
  pinMode(interruptPin1, INPUT);
  
  //attachInterrupt(digitalPinToInterrupt(interruptPin0), chkB, FALLING);

  pinMode(velPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(runPin, OUTPUT);
  
  digitalWrite(velPin, LOW);
  digitalWrite(ledPin, LOW);
  digitalWrite(runPin, LOW);

  delay(5000);

  digitalWrite(runPin, HIGH);
  Serial.begin(9600);
  digitalWrite(ledPin, LOW);
}

uint8_t st = 0;

long initTime = 0;
long starTime = 0;
long waitTime = 0;
long riseTime = 0;
long readAtime = 0;

void loop() {

  if (st == 0) { 
    digitalWrite(velPin, LOW);
    digitalWrite(ledPin, LOW);
  }

  if ((analogRead(A2) > 500) && ((millis() - readAtime) > 1000)) {
    readAtime = millis();
  }
  else if ((analogRead(A2) > 500)) {
    initTime = millis();
    if (st == 0) {
      starTime = millis();
      st = 1;
    }
  }

  

  if (st == 1) {

    analogWrite(velPin, 60);
    
    if ((millis() - starTime) > 30000) {
      st = 2;
      waitTime = millis();
    }
  }

  if (st == 2) {

    analogWrite(velPin, 105);
    
    if ((millis() - waitTime) > 30000) {
      st = 3;
      riseTime = millis();
    }
  }

  if (st == 3) {

    analogWrite(velPin, 129);

    if ((millis() - riseTime) > 15000) {
      st = 2;
      waitTime = millis();
    }
    
  }

  if ((st > 0) && ((millis() - initTime) > 180000)) {
    digitalWrite(ledPin, LOW);
    st = 0;
  }

  //LED
  if ((millis() - starTime) > 30000) {
    digitalWrite(ledPin, HIGH);
  }
  
}


