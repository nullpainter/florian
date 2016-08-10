#include <Arduino.h>
#include "Speakjet.h"

Speakjet::Speakjet(int isSpeakingPin, int txPin) {
  this->isSpeakingPin = isSpeakingPin;

  pinMode(isSpeakingPin, INPUT);

  // Wait for Speakjet to be ready
  while (!(PINB & 0x01));

  serial = new SoftwareSerial(0, txPin);
  serial->begin(9600);
}

Speakjet::~Speakjet() {
  // delete serial;
}

/*
 * Determines if the Speakjet buffer is half full
 */
bool Speakjet::bufferReady() {

  // TODO parameterise this
  return (PINB & (1 << 1)) == LOW;
}

/*
 * Determines if the Speakjet is currently speaking
 */
bool Speakjet::isSpeaking() {
  return digitalRead(isSpeakingPin) == HIGH;
}

void Speakjet::speak(byte command) {
  while (!bufferReady());

  serial->write(command);

   // Wait until Speakjet has finished speaking between words so we can fade out the LED. Speakjet
    // codes 0-6 are pause codes.
    if (command <= 6) {
      while (isSpeaking());
    }

    if (command == END_OF_PHRASE) endOfPhrase = true;
}



/*
 * Plays all Speakjet sounds
 */
void Speakjet::demo() {
  // 200 = sound effects, 128 = all sounds
  for (int i = 128; i <= 254; i++) {
    speak(i);
  }

  while (isSpeaking());
  delay(1000);
}
