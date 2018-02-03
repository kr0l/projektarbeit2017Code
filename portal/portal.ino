#include "FastLED.h"
#include <SoftwareSerial.h>

#define NUM_LEDS 300 //Anzahl der leds der lichterkette
#define color CHSV(hue ++,255, 255); //farbe definieren (hue laesst die farbe wechseln)
#define DATA_PIN 6 //daten pin definieren

CRGBArray<NUM_LEDS> leds;
int segment = 0;
int hue;

void setup() {
   	delay(2000);
      FastLED.addLeds<WS2811, DATA_PIN, BRG>(leds, NUM_LEDS);
      Serial.begin(57600);
      while (!Serial) {
      ; // warten bis die serielle verbindung aufgebaut ist.
      }
      Serial.println("setup ende!"); //in der seriellen verbindung wird setup ende! angezeigt.
}
  int line1 = 3; //hier wird der start der 8 verschiedenen led segmente definiert.
  int line2 = 50;
  int line3 = 50;
  int line4 = 100;
  int line5 = 100;
  int line6 = 150;
  int line7 = 150;
  int line8 = 200;
  int line9 = 200;
  int line10 = 250;
  int line11 = 250;
  int line12 = 300;
  int var = 0;
// start der loop funktion
void loop() {
  scroll();
}

void scroll() {
  do {
    int bline1 = line1;
    int bline2 = line2;
    int bline3 = line3;
    int bline4 = line4;
    int bline5 = line5;
    int bline6 = line6;
    int bline7 = line7;
    int bline8 = line8;
    int bline9 = line9;
    int bline10 = line10;
    int bline11 = line11;
    int bline12 = line12;
    while(var < 50){
    leds[bline1] = color;
    leds[bline2] = color;
    leds[bline3] = color;
    leds[bline4] = color;
    leds[bline5] = color;
    leds[bline6] = color;
    leds[bline7] = color;  
    leds[bline8] = color;
    leds[bline9] = color;
    leds[bline10] = color;
    leds[bline11] = color;
    leds[bline12] = color;
    FastLED.show();
    
    delay(30); //geschwindigkeit in der sich die leds bewegen.
    leds.fadeToBlackBy(80); //hier wird die zeit eingestellt, die es braucht bis die leds aus sind.
    Serial.println(line8);
    var ++; //hier wird eigestellt in welche richtung sich die leds bewegen.
    
    bline1 ++;
    bline2--;
    bline3++;
    bline4--;
    bline5++;
    bline6--;
    bline7++;
    bline8--;
    bline9++;
    bline10--;
    bline11++;
    bline12--;
  }
  } while(true);
}

