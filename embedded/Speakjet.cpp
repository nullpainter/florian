#include <Arduino.h>
#include "Speakjet.h"

Speakjet::Speakjet(int isSpeakingPin, int txPin) {
  this->isSpeakingPin = isSpeakingPin;

  // Wait for Speakjet to be ready
  while (!(PINB & 0x01));

  serial = new SoftwareSerial(0, txPin);
  serial->begin(9600);
}

Speakjet::~Speakjet() {
  // delete serial;
}

bool Speakjet::bufferReady() {
  return (PINB & (1 << 1)) == LOW;
}

bool Speakjet::isSpeaking() {
  return digitalRead(isSpeakingPin) == HIGH;
}

void Speakjet::speak(byte command) {
  while (!bufferReady());

  serial->write(command);
}

void Speakjet::demo() {
  // 200 = sound effects, 128 = all sounds
  for (int i = 128; i <= 254; i++) {
    speak(i);
  }

  while (isSpeaking());
  delay(1000);
}

