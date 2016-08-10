/*
    Note: You must select Raw HID from the "Tools > USB Type" menu
*/
#include <TimerOne.h>

#include "Speakjet.h"
#include "Led.h"
#include "Conductor.h"

#define RED_LED_PIN 5
#define BLUE_LED_PIN 4
#define SPEAKING_PIN 16

#define TX_PIN 8

void speechIndicator();
void startupAnimation();

Speakjet speakjet = Speakjet(SPEAKING_PIN, TX_PIN);

Led redLed = Led(RED_LED_PIN);
Led blueLed = Led(BLUE_LED_PIN);

Conductor conductor = Conductor(&speakjet, &redLed, &blueLed);

/*
   If startup routing is running
*/
volatile bool startup = false;

AnimationStep pulseAnimation[1];

void setup() {

  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(TX_PIN, OUTPUT);

  Serial.begin(9600);
  Serial.println(F("Florian Serial Interface"));

  // Turn on Teensy LED
  digitalWrite(11, HIGH);

  pulseAnimation[0] = AnimationStep(1000, 1000, 500);

  // Start speech LED poll function
  Timer1.initialize(250);
  Timer1.attachInterrupt(speechIndicator);

  //speakjet.demo();

  // Start superfluous startup routine
  startupAnimation();
}

void loop() {
  conductor.poll();
}

/*
   Blinks red LED at regular intervals and blue LED while the Speechjet is speaking a word
*/
void speechIndicator() {

  // Update LED state
  blueLed.update();
  redLed.update();

  // Pulse the red LED during speech
  if (speakjet.isSpeaking()) redLed.startAnimation();

  // If the current phrase has ended, fade out the red LED
  if (speakjet.endOfPhrase) redLed.stopAnimation();

  // Pulse blue LED with speech
  if (!startup) blueLed.fade(speakjet.isSpeaking(), FADE_TIME);
}


AnimationStep animation[7];

void startupAnimation() {
  startup = true;
  redLed.animate(pulseAnimation, sizeof(pulseAnimation) / sizeof(pulseAnimation[0]), true);

  animation[0]  = AnimationStep(500, 250, 0, 0); // Startup delay
  animation[1] =  AnimationStep(125, 250);
  animation[2] =  AnimationStep(125, 50);
  animation[3] =  AnimationStep(125, 250);
  animation[4] =  AnimationStep(25, 50);
  animation[5] =  AnimationStep(25, 50);
  animation[6] =  AnimationStep(500, 1000, 500);

  blueLed.animate(animation, sizeof(animation) / sizeof(animation[0]));
  while (blueLed.sequenceRunning);

  redLed.stopAnimation();
  startup = false;

  // "Ready"
  byte buffer[] = { 20, 96, 201, 200, 202, 203, 0, 0, 148, 131, 177, 128, 255 };
  for (int i = 0; i < (int)sizeof(buffer); i++) {
    speakjet.speak(buffer[i]);
  }
}
