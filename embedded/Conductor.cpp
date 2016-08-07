#include "Conductor.h"

Conductor::Conductor(Speakjet *speakjet, Led *redLed, Led *blueLed) {
  this->speakjet = speakjet;
  this->redLed = redLed;
  this->blueLed = blueLed;
}

void Conductor::poll() {

  // RawHID packets are always 64 bytes
  byte buffer[64];

  int numBytes = RawHID.recv(buffer, 0);
  if (numBytes == 0) return;

  speakjet->endOfPhrase = false;

  Serial.println("Command:");

  for (int i = 0; buffer[i] != END_OF_PHRASE; i++) {
    byte command = buffer[i];
    Serial.print(command);
    Serial.println(" ");


    // Some Speakjet command codes are two byte commands
    if ((i == 0 || !isSpeakjetCommand(buffer[i - 1])) && isReservedCode(command)) {
      // DO led stuff
    }
    else {
      speakjet->speak(command);
    }
  }

  speakjet->speak(END_OF_PHRASE);

  Serial.println("------");

  speakjet->endOfPhrase = true;
}

bool Conductor::isSpeakjetCommand(byte command) {
  return command < RESERVED_START;
}

bool Conductor::isReservedCode(byte command) {
  return command >= RESERVED_START && command <= RESERVED_END;
}
