#include <SoftwareSerial.h>

class Speakjet {
  public:
    Speakjet(int isSpeakingPin, int txPin);
    ~Speakjet();

    bool isSpeaking();

    void speak(byte command);
    void demo();

  private:
    SoftwareSerial *serial;

    int isSpeakingPin;
    bool bufferReady();
};
