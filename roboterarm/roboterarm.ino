#include <Servo.h> //packet zur einfachen benutzung von Servos
#include <SoftwareSerial.h> //packet für serielle verbindungen

//Servos definieren
Servo servoA; //Servo vom untersten segment (Z Fuß)
Servo servoB; //Servo vom ersten segment (Achtung, 2 servos)
Servo servoB2; //Zweiter Servo vom ersten segment
Servo servoC; //Zweites segment (Mittelarm)
Servo servoD; //Drittes segment (Oberarm)
Servo servoE; //Servo zur drehung (Hand)

//Speicherwerte der Istwerte für die Servos.
int istA = 0;
int istB = 0;
int istC = 0;
int istD = 0;
int istE = 0;

//Potentiometer
const int poti1 = A0;
const int poti2 = A1;
const int poti3 = A2;
const int poti4 = A3;
const int poti5 = A4;

int potiVal[4] = {90,90,90,90};
int save1[4] = {90,90,90,90};
int save2[4] = {90,90,90,90};
int save3[4] = {90,90,90,90};
int save4[4] = {90,90,90,90};

//Knöpfe und anschlusspins definieren (const. variablen verändern sich nicht)
const int button1 = 4;
const int button2 = 8;
const int switch1 = 7;
const int led1 = 13;
const int led2 = 12;
const int led3 = 2;
//Status der knöpfe
int button1State = 0;
int button2State = 0;

void setup() {
  //Knöpfe aktivieren
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(switch1, INPUT_PULLUP);
  // servos zu den jeweiligen gpio pins zuordnen:
  servoA.attach(3);
  servoB.attach(5);
  servoB2.attach(6);
  servoC.attach(9);
  servoD.attach(10);
  servoE.attach(11);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  Serial.begin(4800); //Serielle verbindung starten, zum debuggen.
  Serial.println("Hello World!"); //Schreibe den text in den klammern
  ledBoot(5);
  digitalWrite(led1, HIGH);
  digitalWrite(led3, HIGH);
}

void loop() {
  Serial.print(save1[0]);
  Serial.print(save1[1]);
  Serial.print(save1[2]);
  Serial.print(save1[3]);
  Serial.print(save1[4]);
  Serial.print(" ");
    Serial.print(save2[0]);
  Serial.print(save2[1]);
  Serial.print(save2[2]);
  Serial.print(save2[3]);
  Serial.print(save2[4]);
  Serial.print(" ");
    Serial.print(save1[0]);
  Serial.print(save3[1]);
  Serial.print(save3[2]);
  Serial.print(save3[3]);
  Serial.print(save3[4]);
  Serial.print(" ");
  Serial.print(save4[0]);
  Serial.print(save4[1]);
  Serial.print(save4[2]);
  Serial.print(save4[3]);
  Serial.println(save4[4]);
  button1State = digitalRead(button1);
  button2State = digitalRead(button2);
  
  if (digitalRead(button1) == LOW) {
    ledOff();
    digitalWrite(led1, HIGH);
    Serial.println("Drücken Sie den Knopf 2 um die erste Position des Arms zu speichern.");
    //------------Werte Ermitteln--------------//
    //-----------Wert 1-------------------------------------------------//
    do { 
      digitalWrite(led2, HIGH);
      potiLesen(potiVal);
      wertSetzen(potiVal);
      analogWrite(led2, 100);
      if (digitalRead(button2) == LOW) {
        potiLesen(save1);
        delay(20);
      }
      digitalWrite(led2, LOW);
      delay(20);
    } while(digitalRead(button2) == HIGH);
    digitalWrite(led2, LOW);
    delay(500);
    //-----------Wert 2-------------------------------------------------//
    Serial.println("Knopf 2 drücken für die position 2");
    do {
      digitalWrite(led2, HIGH);
      potiLesen(potiVal);
      wertSetzen(potiVal);
      analogWrite(led2, 100);
      if (digitalRead(button2) == LOW) {
        potiLesen(save2);
        delay(20);
      }
      digitalWrite(led2, LOW);
      delay(18);
    } while(digitalRead(button2) == HIGH);
    digitalWrite(led2, LOW);
    delay(500);
    //-----------Wert 3-------------------------------------------------//
    Serial.println("Knopf 2 drücken für die position 3");
    do {
      digitalWrite(led2, HIGH);
      potiLesen(potiVal);
      wertSetzen(potiVal);
      if (digitalRead(button2) == LOW) {
        potiLesen(save3);
        delay(20);
      }
      digitalWrite(led2, LOW);
      delay(15);
    } while(digitalRead(button2) == HIGH);
    digitalWrite(led2, LOW);
    delay(500);
    //-----------Wert 4-------------------------------------------------//
    Serial.println("Knopf 2 drücken um die position 4 zu speichern");
    do {
      digitalWrite(led2, HIGH);
      potiLesen(potiVal);
      wertSetzen(potiVal);
      analogWrite(led2, 100);
      if (digitalRead(button2) == LOW) {
        potiLesen(save4);
        delay(20);
      }
    } while(digitalRead(button2) == HIGH);
    digitalWrite(led2, LOW);

    Serial.println("Alle Positionen wurden gespeichert, drücken Sie Knopf 1 um Fortzufahren.");
    do {
        digitalWrite(led1, LOW);
        delay(200);
        digitalWrite(led1, HIGH);
        delay(200);
      } while(digitalRead(button1) == HIGH);
    delay(500);
    ledOn();
  }
  if (digitalRead(button2) == LOW) {
    ledOff();
    Serial.println("Beginn knopf 2");
    digitalWrite(led2, HIGH);
    delay(1000);
    do {
      wertSetzen(save1);
      if(digitalRead(button2) == LOW) {
        break;
      }
      delay(500);
      wertSetzen(save2);
      if(digitalRead(button2) == LOW) {
        break;
      }
      delay(500);
      wertSetzen(save3);
      if(digitalRead(button2) == LOW) {
        break;
      }
      delay(500);
      wertSetzen(save4);
      if(digitalRead(button2) == LOW) {
        break;
      }
      delay(500);
    }while(true);
    ledOn();
    delay(1000);
  }
  //Wenn der schalter an ist, mach dass, was die Potentiometer machen
  if (digitalRead(switch1) == LOW) {
    ledOff();
    digitalWrite(led3, HIGH);
    delay(1000);
    do {
      Serial.println("switch");
      potiLesen(potiVal);
      wertSetzen2(potiVal[0], potiVal[1], potiVal[2], potiVal[3], potiVal[4]);
    } while(digitalRead(switch1) == HIGH);
    digitalWrite(led3, LOW);
    delay(1000);
    ledOn();
  }
  //Serial.println("new loop");
}
void wertSetzen(int arrayname[]) {
  wertSetzen2(arrayname[0], arrayname[1], arrayname[2], arrayname[3], arrayname[4]);
}
void potiLesen(int variable[]) {

  variable[0] = map(analogRead(poti1), 0, 1023, 0, 180);
  variable[1] = map(analogRead(poti2), 0, 1023, 0, 180);
  variable[2] = map(analogRead(poti3), 400, 1023, 0, 180);
  variable[3] = map(analogRead(poti4), 0, 1023, 0, 180);
  variable[4] = map(analogRead(poti5), 0, 1023, 0, 180);
  Serial.print(variable[0]);
  Serial.print(" ");
  Serial.print(variable[1]);
  Serial.print(" ");
  Serial.print(variable[2]);
  Serial.print(" ");
  Serial.println(variable[3]);
  
/*
  potiVal[0] = 10;
  potiVal[1] = 20;
  potiVal[2] = 30;
  potiVal[3] = 40;
  potiVal[4] = 50;
  */
}

void wertSetzen2(int a, int b, int c, int d, int e) {
  

  do {
    if (istA < a) {
      servoA.write((istA - 180)*-1);
      istA++;
    }
    else if (istA > a) {
      servoA.write((istA - 180)*-1);
      istA--;
    }
    if (istB < b) {
      servoB.write((istB - 180)*-1);
      servoB2.write(istB);
      istB++;
    }
    else if (istB > b) {
      servoB.write((istB - 180)*-1);
      servoB2.write(istB);
      istB--;
    }
    if (istC < c) {
      servoC.write((istC - 180)*-1);
      istC++;
    }
    else if (istC > c) {
      servoC.write((istC - 180)*-1);
      istC--;
    }
    if (istD < d) {
      servoD.write((istD - 180)*-1);
      istD++;
    }
    else if (istD > d) {
      servoD.write((istD - 180)*-1);
      istD--;
    }
    if (istE < e) {
      servoE.write((istE - 180)*-1);
      istE++;
    }
    else if (istE > e) {
      servoE.write((istE - 180)*-1);
      istE--;
    }
    delay(20);
  } while(istA != a || istB != b || istC != c || istD != d || istE != e);
}
void ledBoot(int anzahl) {
  for(int i = 0; i < anzahl; i++) {
    digitalWrite(led1, HIGH);
    delay(100);
    digitalWrite(led2, HIGH);
    delay(100);
    digitalWrite(led3, HIGH);
    delay(100);
    digitalWrite(led1, LOW);
    delay(100);
    digitalWrite(led2, LOW);
    delay(100);
    digitalWrite(led3, LOW);
    delay(100);
  }
}
void ledOn() {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
}
void ledOff() {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
}

