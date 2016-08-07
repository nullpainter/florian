#include "Speakjet.h"
#include "Led.h"

// Raw HID command definitions
#define RED_ON 32
#define LED_DURATION 33
#define BLUE_ON 34

// Speakjet ommand codes are 0-31
#define RESERVED_START 32
#define RESERVED_END 127

class Conductor {
  public:
    Conductor(Speakjet *speakjet, Led *redLed, Led *blueLed);
    void poll();
  private:
    Speakjet *speakjet;
    Led *redLed;
    Led *blueLed;

    bool isSpeakjetCommand(byte command);
    bool isReservedCode(byte command);
};
