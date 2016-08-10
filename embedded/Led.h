#pragma once

#include <LEDFader.h>

#define FADE_TIME 150


class AnimationStep {
  public:
    AnimationStep();
    AnimationStep(unsigned int onDuration, unsigned int offDuration = 0, unsigned int fadeDuration = 20, unsigned int maxIntensity = 255);

    unsigned int fadeDuration;
    unsigned int onDuration;
    unsigned int offDuration;
    unsigned int maxIntensity;
};


class Led {
  public:
    Led(int ledPin);
    ~Led();

    /*
       Fade the LED in or out. This function can be safely called while the LED is fading or if
       the fade has completed.
    */
    void fade(bool fadeIn, int durationMs);

    /*
      Blocks until the current fade has completed
    */
    void waitForFade();


    /*
       Determines if the current fade has completed
    */
    bool isFadeFinished();

    /**
       Updates LED animation and fading. This should be called as frequency as practical.
    */
    void update();

    /*
       Waits for the current animation frame to end, and stops the animation
    */
    void stopAnimation();

    /*
       Starts an animation. Only required to be called after a previous call to stopAnimation()
    */
    void startAnimation();

    /*
      Pulses the LED at regular intervals as defined by LED_PULSE_MS
    */
    void pulse();
    void animate(AnimationStep sequence[], int sequenceCount, bool sequenceLooped = false);

    volatile bool sequenceRunning = false;
  private:
    LEDFader *led;
    int targetFade;
    bool pulseFadingIn = true;
    int animationPulseStep = 0;

    // Timing pulse sequence, in ms
    AnimationStep *sequence;
    bool sequenceLooped = false;
    unsigned int sequenceStep = 0;
    unsigned int sequenceCount;
    unsigned long previousSequenceMillis = 0;
    unsigned long previousMillis = 0;
    bool animationStopRequested = false;

    void fade(int target, int durationMs);
    void waitForFade(int value);
    void updateAnimation();
};

