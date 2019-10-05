
#include <Controllino.h>

const byte interruptPin0 = CONTROLLINO_IN0;
const byte interruptPin1 = CONTROLLINO_IN1;

const byte runPin = CONTROLLINO_D1;
const byte velPin = CONTROLLINO_D2;
const byte ledPin = CONTROLLINO_D4;

const byte senPin = CONTROLLINO_A2;
const byte powPin = CONTROLLINO_A4;

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

  //digitalWrite(runPin, HIGH);
  //Serial.begin(9600);
  digitalWrite(ledPin, LOW);
}

uint8_t st = 0;

long initTime = 0;
long starTime = 0;
long waitTime = 0;
long riseTime = 0;
long readAtime = 0;
long endTime = 0;

bool sensPushed = false;
long sensTimer = 0;

void loop() {

  //  Function: MAIN SWITCH
  while (analogRead(powPin) < 600) {
    Serial.println("spento");
    st = 0;
    digitalWrite(velPin, LOW);
    digitalWrite(ledPin, LOW);
    delay(5000);
    digitalWrite(runPin, LOW);
    
  }
  digitalWrite(runPin, HIGH);
  //Serial.println((millis() - initTime));

  //  IDLE 
  if (st == 0) { 

    digitalWrite(velPin, LOW);
    digitalWrite(ledPin, LOW);
  }

  //  Function: SENSOR  TRIGGERED
  if ((analogRead(CONTROLLINO_A2) > 600) && ((millis() - readAtime) > 1000)) {
    initTime = millis();
    
    if (st == 0) {
      starTime = millis();
      st = 1;
    }
  }

  
  

  //  Function: ENDING (after 3 minutes)
  if (((millis() - initTime) > 180000) && st < 4) {
    st = 4;
    endTime = millis();
  }

  
  
  //  WAKING UP
  if (st == 1) {

    analogWrite(velPin, 50); //60
    
    if ((millis() - starTime) > 30000) {
      st = 2;
      digitalWrite(ledPin, HIGH);
      waitTime = millis();
    }
  }


  // STEADY
  if (st == 2) {

    analogWrite(velPin, 95);  //105
    
    if ((millis() - waitTime) > 30000) {
      st = 3;
      riseTime = millis();
    }
  }


  // EXCITED
  if (st == 3) {

    analogWrite(velPin, 119); //129

    if ((millis() - riseTime) > 15000) {
      st = 2;
      waitTime = millis();
    }
    
  }

  // ENDING
  if (st == 4) {

    analogWrite(velPin, 0);

    if ((millis() - endTime) > 10000) {
      st = 0;
      digitalWrite(ledPin, LOW);
    }
    
  }

  
}
