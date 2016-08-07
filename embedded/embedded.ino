/*
    Note: You must select Raw HID from the "Tools > USB Type" menu
*/
#include <TimerOne.h>

#include "Speakjet.h"
#include "Led.h"

#define RED_LED_PIN 5
#define BLUE_LED_PIN 4
#define SPEAKING_PIN 16
#define FADE_TIME 100

#define TX_PIN 8

#define LED_PULSE_MS 500

void speechIndicator();
void startupAnimation();
void speak (int numBytes);

Speakjet speakjet = Speakjet(SPEAKING_PIN, TX_PIN);

Led redLed = Led(RED_LED_PIN);
Led blueLed = Led(BLUE_LED_PIN);

void setup() {

  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(TX_PIN, OUTPUT);

  Serial.begin(9600);
  Serial.println(F("Florian"));
  /*
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(BLUE_LED_PIN, HIGH);
    while(true);
  */

  // Configure port B for input
  DDRB = 0x00;
  PORTB = 0x00;

  // Configure unused pins for output to save power
  DDRC = 0xF;
  DDRE = 0xF;
  DDRF = 0xF;


  // Turn on LED
  digitalWrite(11, HIGH);

  pinMode(PF7, INPUT);

  Timer1.initialize(250);
  Timer1.attachInterrupt(speechIndicator);

  // speakjet.demo();
  startupAnimation();
}


// RawHID packets are always 64 bytes
byte buffer[64];

volatile bool endOfSpeech = false;

void loop() {

  int numBytes = RawHID.recv(buffer, 0); // 0 timeout = do not wait
  if (numBytes > 0) {
    speak(numBytes);
  }
}

void speak (int numBytes) {
  endOfSpeech = false;
  for (int i = 0; i < numBytes; i++) {

    // If special end-of-buffer byte has been reached, break as there's no more data to read
    if (buffer[i] == 255) {
      endOfSpeech = true;
      break;
    }

    // Wait until Speakjet has finished speaking between words so we can fade out the LED
    if (buffer[i] == 0) {
      while (speakjet.isSpeaking());
    }

    // Write byte to Speakjet
    speakjet.speak(buffer[i]);
  }
}

unsigned long previousMillis = 0;
bool fadingIn = true;
volatile bool startup = false;

bool readyForLedPulse() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= LED_PULSE_MS) {
    previousMillis = currentMillis;
    return true;
  }

  return false;
}

void pulseLed() {
  if (!readyForLedPulse()) return;

  redLed.fade(fadingIn, FADE_TIME);
  fadingIn = !fadingIn;
}

void speechIndicator() {

  // Update LED state
  blueLed.update();
  redLed.update();

  // If the current phrase has ended, fade out the red LED
  if (endOfSpeech && readyForLedPulse()) redLed.fade((bool)false, FADE_TIME);

  // Pulse the red LED at startup and during speech
  if (startup || speakjet.isSpeaking()) pulseLed();

  // Pulse blue LED with speech
  blueLed.fade(speakjet.isSpeaking(), FADE_TIME);
}

void startupAnimation() {
  startup = true;
  delay(LED_PULSE_MS * 4);
  startup = false;

  // "Ready"
  buffer[0] = 148;
  buffer[1] = 131;
  buffer[2] = 181;
  buffer[3] = 128;
  buffer[4] = 255;

  speak(6);
}
