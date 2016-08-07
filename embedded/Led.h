#include <LEDFader.h>

class Led {
  public:
    Led(int ledPin);
    ~Led();

    void fade(bool fadeIn, int durationMs);
    void waitForFade();
    bool isFadeFinished();
    void update();

  private:
    LEDFader *led;
    int targetFade;

    void fade(int target, int durationMs);
    void waitForFade(int value);
};
