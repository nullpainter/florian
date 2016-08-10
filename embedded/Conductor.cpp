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
  bool redOn = false;
  bool blueOn = false;

  for (int i = 0; i < (int)sizeof(buffer); i++) {
    byte command = buffer[i];
   
    // Some Speakjet command codes are two byte commands
    if ((i == 0 || !isSpeakjetCommand(buffer[i - 1])) && isReservedCode(command)) {
      switch(command) {
        case RED_ON:
        redOn = true;
        break;
        case BLUE_ON:
        blueOn = true;
        break;
        case LED_DURATION:
          // todo netx buyte is the duration
            break;
      }
    }
    else {
      speakjet->speak(command);
    }

    if (command == END_OF_PHRASE) break;
  }
}

bool Conductor::isSpeakjetCommand(byte command) {
  return command < RESERVED_START;
}

bool Conductor::isReservedCode(byte command) {
  return command >= RESERVED_START && command <= RESERVED_END;
}
