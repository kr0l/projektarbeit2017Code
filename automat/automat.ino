#define DISTANCE 20
#include <SoftwareSerial.h>
//Serielle verbindung
SoftwareSerial mySerial(10, 11); // RX, TX

int StepCounter = 0;
int Stepping1 = false;
int Stepping2 = false;
int Stepping3 = false;
int stepper;
int stepperRichtung;

void setup() {                
  pinMode(8, OUTPUT); // Driver 1 STEP
  pinMode(9, OUTPUT); // Driver 1 DIR
  pinMode(7, OUTPUT); // Driver 2 STEP
  pinMode(6, OUTPUT); // Driver 2 DIR
  digitalWrite(8, LOW); 
  digitalWrite(9, LOW); 
  digitalWrite(7, LOW); 
  digitalWrite(6, LOW); 

  pinMode(10, INPUT); //Button 1
  pinMode(11, INPUT); //Button 2
  pinMode(12, INPUT); //Button 3

   // Open serial communications and wait for port to open:
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Hello World");
}

void loop() {
  if (digitalRead(10) == LOW) //Abfrage des ersten Knopfes
  {
    Stepping1 = true;
    Serial.println("Erster Knopf Gedrückt");
  }
  if (digitalRead(11) == LOW) //Abfrage des zweiten Knopfes
  {
    Stepping2 = true; 
    Serial.println("Zweiter Knopf Gedrückt");
  }
  if (digitalRead(12) == LOW) //Abfrage des dritten Knopfes
  {
    Stepping3 = true;
    Serial.println("Dritter Knopf Gedrückt");
  }
 //Befehle wenn die Knoepfe gedrueckt werden
  if (Stepping1 == true) //Befehle wenn die Knoepfe gedrueckt werden
  {
    auf(7,6,3200);
    zu(7,6,3200);
    auf(9,8,600);
    zu(9,8,600);
  }
  if (Stepping2 == true)
  {
    auf(7,6,2000);
    zu(7,6,2000);
    auf(9,8,2000);
    zu(9,8,2000);
  }
  if (Stepping3 == true)
  {
    auf(7,6,600);
    zu(7,6,600);
    auf(9,8,3200);
    zu(9,8,3200);
  }
}

void auf(int stepper, int stepperRichtung, int counter) //Erste Bewegung eines Beliebigen Motors
  {
    do {
      
      digitalWrite(stepper, HIGH);
      delayMicroseconds(500);          
      digitalWrite(stepper, LOW); 
      delayMicroseconds(500);
      StepCounter = StepCounter + 1;
      
    } while (StepCounter < counter);
    Stepping1 = false;
    Stepping2 = false;
    Stepping3 = false;
    StepCounter = 0;
    digitalWrite(stepperRichtung, HIGH);
    Serial.println("Erste Bewegung");
    
  }

void zu(int stepper, int stepperRichtung, int counter) //Zweite Bewegung eines Belibigen Motors
  {
    do {
      
      digitalWrite(stepper, LOW);
      delayMicroseconds(500);          
      digitalWrite(stepper, HIGH); 
      delayMicroseconds(500);
      StepCounter = StepCounter + 1;
      
    } while (StepCounter < counter);
    StepCounter = 0;
    digitalWrite(stepperRichtung, LOW);
    Serial.println("Zweite Bewegung");
    
  }