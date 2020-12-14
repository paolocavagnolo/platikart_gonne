
#include <Controllino.h>

#define runPin CONTROLLINO_D1
#define velPin CONTROLLINO_D2
#define ledPin CONTROLLINO_D4
#define ebPin CONTROLLINO_D0 //NEW!!

#define senPin CONTROLLINO_A2
#define powPin CONTROLLINO_A4
#define modPin CONTROLLINO_A0


void setup() {

  pinMode(velPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(runPin, OUTPUT);
  pinMode(ebPin, OUTPUT);

  digitalWrite(velPin, LOW);
  digitalWrite(ledPin, LOW);
  digitalWrite(runPin, LOW);
  digitalWrite(ebPin, LOW);

  delay(5000);

  digitalWrite(ledPin, LOW);

}



uint8_t st = 0;

long initTime = 0;
long starTime = 0;
long waitTime = 0;
long riseTime = 0;
long endTime = 0;

bool sensPushed = false;
long sensTimer = 0;



void loop() {


  if (analogRead(powPin) < 600) {

    Serial.println("spento");
    st = 0;
    digitalWrite(velPin, LOW);
    digitalWrite(ledPin, LOW);
    delay(5000);
    digitalWrite(runPin, LOW);

    if (analogRead(modPin) > 600) {
      digitalWrite(ebPin, HIGH);
    }
    
  }

  else {

      digitalWrite(runPin, HIGH);

      //  Function: SENSOR  TRIGGERED
      if ((analogRead(CONTROLLINO_A2) > 600)) {
        initTime = millis();
        
        if (st == 0) {
          starTime = millis();
          if (analogRead(modPin) > 600) {
            digitalWrite(ebPin, LOW);
          }
          st = 1;
        }
      }

      //  Function: ENDING (after 3 minutes)
      if (((millis() - initTime) > 180000) && st < 4 && st > 0) {
        st = 4;
        endTime = millis();
      }

      
      //  IDLE 
      if (st == 0) { 

        digitalWrite(velPin, LOW);
        digitalWrite(ledPin, LOW);
        
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

          if (analogRead(modPin) > 600) {
            digitalWrite(ebPin, HIGH);
          }
          
        }
        
      }
  }
  

  
}
