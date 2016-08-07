/*
    Note: You must select Raw HID from the "Tools > USB Type" menu
*/
#include <TimerOne.h>

#include "Speakjet.h"
#include "Led.h"

#define RED_LED_PIN 5
#define BLUE_LED_PIN 4
#define SPEAKING_PIN 16

#define TX_PIN 8

void speechIndicator();
void startupAnimation();

Speakjet speakjet = Speakjet(SPEAKING_PIN, TX_PIN);

Led redLed = Led(RED_LED_PIN);
Led blueLed = Led(BLUE_LED_PIN);

/*
 * If startup routing is running
 */
volatile bool startup = false;

void setup() {

  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(TX_PIN, OUTPUT);

  Serial.begin(9600);
  Serial.println(F("Florian Serial Interface"));

  // Light placement test
  if (false) {
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(BLUE_LED_PIN, HIGH);
    while (true);
  }

  // Turn on Teensy LED
  digitalWrite(11, HIGH);

  // Start speech LED poll function
  Timer1.initialize(250);
  Timer1.attachInterrupt(speechIndicator);

  // speakjet.demo();

  // Start superfluous startup routine
  startupAnimation();
}

void loop() {
  speakjet.poll();
}

/*
 * Blinks red LED at regular intervals and blue LED while the Speechjet is speaking a word
 */
void speechIndicator() {

  // Update LED state
  blueLed.update();
  redLed.update();

  // Pulse the red LED at startup and during speech
  if (startup || speakjet.isSpeaking()) redLed.pulse();

  // If the current phrase has ended, fade out the red LED
  if (speakjet.isEndOfPhrase() && redLed.readyForLedPulse()) redLed.fade((bool)false, FADE_TIME);

  // Pulse blue LED with speech
  blueLed.fade(speakjet.isSpeaking(), FADE_TIME);
}

void startupAnimation() {
  startup = true;
  delay(LED_PULSE_MS * 4);
  startup = false;

  // "Ready"
  byte buffer[64] = { 201, 200, 202, 203, 0, 0, 148 , 131, 177, 128, 255 };
  speakjet.speak(buffer);
}
