#pragma once

#include <SoftwareSerial.h>
#include "Arduino.h"

#define END_OF_PHRASE 255

class Speakjet {
  public:
    Speakjet(int isSpeakingPin, int txPin);
    ~Speakjet();

    volatile bool endOfPhrase = false;

    bool isSpeaking();
    void speak(byte command);
    void speak(byte buffer[]);
    void poll();
    void demo();

  private:
    SoftwareSerial *serial;
    
    int isSpeakingPin;
    bool bufferReady();
};
