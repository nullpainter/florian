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

bool Speakjet::isEndOfPhrase() {
  return endOfPhrase;
}

void Speakjet::speak(byte buffer[]) {
  endOfPhrase = false;

  for (int i = 0; buffer[i] != END_OF_PHRASE; i++) {

    // Wait until Speakjet has finished speaking between words so we can fade out the LED
    if (buffer[i] == 0) {
      while (isSpeaking());
    }

    // Write byte to Speakjet
    speak(buffer[i]);
  }

  endOfPhrase = true;
}

void Speakjet::poll() {
 
  // RawHID packets are always 64 bytes
  byte buffer[64];

  int numBytes = RawHID.recv(buffer, 0);
  if (numBytes > 0) {
    speak(buffer);
  }
}

