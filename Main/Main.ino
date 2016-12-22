#include <FillPat.h>
#include <LaunchPad.h>
#include <OrbitBoosterPackDefs.h>
#include <OrbitOled.h> 
#include <OrbitOledChar.h>
#include <OrbitOledGrph.h>
#include <stdlib.h>
#include <stdio.h>

void initAccel();
void initWire();
int initGame();
void homeScreen();
void moveCharacter();
const int buttonPinUp = PE_0;
const int buttonPinDown = PD_2;

void setup() {
  OrbitOledSetCharUpdate(0);
  OrbitOledInit();
  pinMode(buttonPinUp, INPUT);
  pinMode(buttonPinDown, INPUT);
  randomSeed(analogRead(0));
  initWire();
  initAccel();
  Serial.begin(9600);
}

void loop() {
  homeScreen();
  moveCharacter();
}
