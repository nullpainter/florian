#include "Led.h"

Led::Led(int ledPin) {
  led = new LEDFader(ledPin);
}

Led::~Led() {
  delete led;
}

void Led::update() {
  updateAnimation();
  this->led->update();
}

void Led::updateAnimation() {
  if (!sequenceRunning) return;

  unsigned long currentMillis = millis();


  AnimationStep step = sequence[sequenceStep];

  // Return if current animation step is still fading in or on
  if (currentMillis - previousSequenceMillis < step.onDuration + step.fadeDuration) return;

  // Check if current animation step has already faded out
  if (currentMillis - previousSequenceMillis >= step.onDuration + step.fadeDuration * 2 + step.offDuration) {

    // If we've completed the final step or we have been requested to end the sequence, stop the sequence
    if (sequenceStep == sequenceCount - 1 || animationStopRequested) {
      sequenceRunning = false;

      Serial.println("Stopping");

      if (!animationStopRequested) {
        if (sequenceLooped) {
          startAnimation();
        }
        else {
          Serial.println("Deallocating sequence");
          delete &sequence;
        }
      }
    }
    else {

      // Fade the next animation step in
      fade((int)step.maxIntensity, step.fadeDuration);
      sequenceStep++;
      previousSequenceMillis = currentMillis;

    }
  }
  else {

    // If we're not ready for the next animation step, fade the current step out
    fade((int)0, step.fadeDuration);
  }
}

void Led::stopAnimation() {
  animationStopRequested = true;
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

void Led::animate(AnimationStep sequence[], int sequenceCount, bool sequenceLooped) {

  this->sequence = sequence;
  this->sequenceCount = sequenceCount;
  this->sequenceLooped = sequenceLooped;

  startAnimation();
}

void Led::startAnimation() {
  if (sequenceRunning || sequence == NULL) return;

  sequenceStep = 0;
  animationStopRequested = false;
  sequenceRunning = true;

  previousSequenceMillis = millis();

  AnimationStep step = sequence[sequenceStep];
  fade((int)step.maxIntensity, step.fadeDuration);
}

/*
   Fade the LED in or out. This function can be safely called while the LED is fading or if
   the fade has completed.

   @param target target intensity, 0-255
   @param durationMs duration of fade
*/
void Led::fade(int target, int durationMs) {
  targetFade = target;

  // Don't fade if we're already fading or have reached the target
  if (led->is_fading() || isFadeFinished()) return;
  Serial.print("Fading to ");
  Serial.print(target);
  Serial.print(" over ");
  Serial.print(durationMs);
  Serial.println("ms");
  led->fade(target, durationMs);
}

AnimationStep::AnimationStep() {
}

AnimationStep::AnimationStep(unsigned int onDuration, unsigned int offDuration, unsigned int fadeDuration, unsigned int maxIntensity) {
  this->onDuration = onDuration;
  this->offDuration = offDuration;
  this->fadeDuration = fadeDuration;
  this->maxIntensity = maxIntensity;
}

