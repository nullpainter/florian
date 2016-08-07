#include "Led.h"

Led::Led(int ledPin) {
  led = new LEDFader(ledPin);
}

Led::~Led() {
  delete led;
}

/*
 * Updates the internal LED animation
 */
void Led::update() {
  this->led->update();
}

/*
 * Fade the LED in or out. This function can be safely called while the LED is fading or if
 * the fade has completed.
 */
void Led::fade(bool fadeIn, int durationMs) {
  fade(fadeIn ? 255 : 0, durationMs);
}

/*
 * Determines if the current fade has completed
 */
bool Led::isFadeFinished() {
  return led->get_value() == targetFade;
}

/*
 * Blocks until the current fade has completed
 */
void Led::waitForFade() {
  while (!isFadeFinished()) update();
}

/*
 * Pulses the LED at regular intervals as defined by LED_PULSE_MS
 */
void Led::pulse() {
  if (!readyForLedPulse()) return;

  fade(pulseFadingIn, FADE_TIME);
  pulseFadingIn = !pulseFadingIn;
}

/*
 * Fade the LED in or out. This function can be safely called while the LED is fading or if
 * the fade has completed.
 * 
 * @param target target intensity, 0-255
 * @param durationMs duration of fade
 */
void Led::fade(int target, int durationMs) {
  targetFade = target;

  // Don't fade if we're already fading or have reached the target
  if (led->is_fading() || isFadeFinished()) return;

  led->fade(target, durationMs);
}

/*
 * Determines if the LED is ready for a pulse, as defined by LED_PULSE_MS elapsing
 * 
 * @see pulse()
 */
bool Led::readyForLedPulse() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= LED_PULSE_MS) {
    previousMillis = currentMillis;
    return true;
  }

  return false;
}

