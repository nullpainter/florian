#include <SoftwareSerial.h>
#define END_OF_PHRASE 255

class Speakjet {
  public:
    Speakjet(int isSpeakingPin, int txPin);
    ~Speakjet();

    bool isSpeaking();
    bool isEndOfPhrase();
    void speak(byte command);
    void speak(byte buffer[]);
    void poll();
    void demo();

  private:
    SoftwareSerial *serial;
    volatile bool endOfPhrase = false;
 
    // RawHID packets are always 64 bytes
    byte buffer[64];

    int isSpeakingPin;
    bool bufferReady();
};
