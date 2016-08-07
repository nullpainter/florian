#include "Led.h"

Led::Led(int ledPin) {
  led = new LEDFader(ledPin);
}

Led::~Led() {
  delete led;
}

void Led::update() {
  this->led->update();
}

void Led::fade(bool fadeIn, int durationMs) {
  fade(fadeIn ? 255 : 0, durationMs);
}

bool Led::isFadeFinished() {
  return led->get_value() == targetFade;
}

void Led::waitForFade() {
  while (!isFadeFinished()) update();
}

void Led::fade(int target, int durationMs) {
  targetFade = target;

  // Don't fade if we're already fading or have reached the target
  if (led->is_fading() || isFadeFinished()) return;

  led->fade(target, durationMs);
}
