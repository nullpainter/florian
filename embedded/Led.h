#pragma once

#include <LEDFader.h>

#define LED_PULSE_MS 500
#define FADE_TIME 150

class Led {
  public:
    Led(int ledPin);
    ~Led();

    void fade(bool fadeIn, int durationMs);
    void waitForFade();
    bool isFadeFinished();
    void update();
    bool readyForLedPulse();
    void pulse();
  private:
    LEDFader *led;
    int targetFade;
    bool pulseFadingIn = true;
    unsigned long previousMillis = 0;
    

    void fade(int target, int durationMs);
    void waitForFade(int value);
};
