#include <Arduino.h>
#include <Bounce2.h>
#include "4x14LED.h"
#include <Wire.h>
// #include "i2cscanner.h"

void readEncoder();
void rotateEncoder();

// encoder btn pin
#define ENC_BTN_PIN 7
#define ENC_A 6
#define ENV_B 3
#define LED_PIN 10

const int unilen = 3;
int universeLaters[26] = {
  247,  // A
  4751, // B
  57,   // C
  4623, // D
  121,  // E
  113,  // F
  189,  // G 
  246,  // H
  4617, // I
  30,   // J
  9328, // K
  56,   // L
  1334, // M
  8502, // N
  63,   // O
  243,  // P
  8255, // Q
  8435, // R
  219,  // S
  4609, // T
  62,   // U
  3120, // V
  10294,// W
  11520,// X
  5376, // Y
  3081, // Z
  };
int intag[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int randUni[unilen + 1];
bool ledStatus = false;

HT4x14LED led;
// I2CSCANNER scanner;

volatile bool encAStatus = false; //debounced encoder switch reads
volatile bool encBStatus = false;
volatile bool encBtnStatus = false;

Bounce bounceBTN = Bounce();
Bounce bounceEncA = Bounce();
Bounce bounceEncB = Bounce();

int randomUniverseNumber = 0;
int randomUniverseLater = -1;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  Serial.println("Stert setup");
  bounceBTN.attach(ENC_BTN_PIN, INPUT_PULLUP);
  bounceBTN.interval(5);
  bounceEncA.attach(ENC_A, INPUT_PULLUP);
  bounceEncA.interval(2);
  bounceEncB.attach(ENV_B, INPUT_PULLUP);
  bounceEncB.interval(2);
  pinMode(LED_PIN, OUTPUT);
  led.init(1);
  led.brig(10);
  led.blink(1);
  led.clear();
  Serial.print("End setup");
}


void loop() {
  bounceBTN.update();
  bounceEncA.update();
  bounceEncB.update();

  readEncoder();
  if (encBtnStatus && !encAStatus && !encBStatus) {
    Serial.print("click ");
    if ( ledStatus == false) {
      digitalWrite(LED_PIN, HIGH);
      ledStatus = true;
    } else {
      digitalWrite(LED_PIN, LOW);
      ledStatus = false;
    }
    Serial.println(ledStatus);
    encBtnStatus = false;
  }
  if (!encBtnStatus && encAStatus && encBStatus) {
    rotateEncoder();
  }
  if (!encBtnStatus && encAStatus && !encBStatus) {
    rotateEncoder();
  }
  led.print(randomUniverseNumber,0,randomUniverseLater,-1,-1,-1);
}

void rotateEncoder() {
  randomUniverseNumber = random(0, 999);
  randomUniverseLater = universeLaters[random(0, 26)];
  encAStatus = false;
  encBStatus = false;
  Serial.println(randomUniverseNumber);
}


void readEncoder() {
  if (bounceBTN.changed()) {
    encBtnStatus = bounceBTN.read();
  }
  if (bounceEncA.changed()) {
    encAStatus = bounceEncA.read();
  }
  if (bounceEncB.changed()) {
    encBStatus = bounceEncB.read();
  }
}