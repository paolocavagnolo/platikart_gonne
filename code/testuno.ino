#include <Controllino.h>

const byte enablePin = CONTROLLINO_D0;
const byte dirPin = CONTROLLINO_D1;
const byte velPin = CONTROLLINO_D2;

const byte enc0Pin = CONTROLLINO_A0;
const byte enc1Pin = CONTROLLINO_A1;

const byte switchPinA = CONTROLLINO_A3;
const byte switchPinB = CONTROLLINO_A4;

const byte interruptPin0 = CONTROLLINO_IN0;
const byte interruptPin1 = CONTROLLINO_IN1;
volatile int incrA = 0;
volatile long iniA = 0;
volatile int incrB = 0;
volatile long iniB = 0;

uint8_t minimo = 1;
uint8_t massimo = 52;

int massimoB = 25;

void setup() {

  pinMode(enablePin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(velPin, OUTPUT);
  pinMode(CONTROLLINO_D4, OUTPUT);
  pinMode(CONTROLLINO_D5, OUTPUT);

  pinMode(enc0Pin, INPUT);
  pinMode(enc1Pin, INPUT);
  pinMode(switchPinA, INPUT);
  pinMode(switchPinB, INPUT);

 pinMode(interruptPin0, INPUT);
 pinMode(interruptPin1, INPUT);
 
 attachInterrupt(digitalPinToInterrupt(interruptPin0), chkA, FALLING);
 attachInterrupt(digitalPinToInterrupt(interruptPin1), chkB, FALLING);

 digitalWrite(CONTROLLINO_D4, HIGH);
 digitalWrite(CONTROLLINO_D5, HIGH);
 Serial.begin(9600);
}

uint8_t veloc = 0;
uint8_t veloStat = 0;
uint8_t veloSin = 0;
bool prime = true;
bool ret = true;
float freq = 0;
float period = 0;


void loop() {

  if (analogRead(switchPinA) < 500) {
  
    spegni();
  
  }
  else {
    
    accendi();
  
  }

}


void spegni() {
  digitalWrite(enablePin, LOW);
  digitalWrite(velPin, 0);
  incrA = 0;
  incrB = 0;
}

void accendi() {
  digitalWrite(enablePin, HIGH);
}

void chkA() {
 
 if ((digitalRead(enc0Pin)) && ((micros() - iniA) > 10000)) {
  incrA++;
  if (incrA > massimo-1) {
    incrA = massimo;
  }
  iniA = micros();
 }
 else if ((micros() - iniA) > 10000) {
  incrA--;
  if (incrA < 1) {
    incrA = 0;
  }
  iniA = micros();
 }
}

void chkB() {
 if ((digitalRead(enc1Pin)) && ((micros() - iniB) > 10000)) {
  incrB++;  if (incrA < 1) {
    
  }
  if (incrB > massimoB-1) {
    incrB = massimoB;
  }
  iniB = micros();
 }
 else if ((micros() - iniB) > 10000) {
  incrB--;
  if (incrB < 1) {
    incrB = 0;
  }
  iniB = micros();
 }
}
