#include <Arduino.h>

class PushButton {

public:
    PushButton(uint8_t pin);

private:
    void handleInterrupt();

    uint8_t m_pin{ 0 };
    static volatile uint8_t m_counter;
};
