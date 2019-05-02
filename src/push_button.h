#pragma once
#include <Arduino.h>
#include <Ticker.h>

namespace pb {
class PushButton {

    static const uint8_t SEQUENCE_LENGTH = 6;

    static const uint32_t DEBOUNCE_MILLIS = 25;
    static const uint32_t MAX_MILLIS_SHORT_PRESS = 500;
    static const uint32_t MAX_MILLIS_LONG_PRESS = 2000;
    static const uint32_t MAX_MILLIS_LONG_HOLD = 3000;
    static const uint32_t MAX_MILLIS_MULTI_PRESS_GAP = 250;

public:
    enum class Event : uint8_t {
        NONE,
        SHORT_PRESS,
        LONG_PRESS,
        LONG_HOLD,
        DOUBLE_PRESS,
        TRIPLE_PRESS,
        NOT_READY,
        INVALID
    };

    PushButton(uint8_t pin);
    PushButton(uint8_t pin, uint8_t initialEdge);

    void attach();
    void detach();

    Event getEvent();

private:
    void handleInterrupt();
    void reset();

    uint8_t m_pin;
    uint8_t m_initial_edge;

    Ticker m_ticker;

    volatile uint8_t m_sequence;
    volatile uint8_t m_expected_interrupt_edge;

    volatile uint32_t m_sequence_timer[SEQUENCE_LENGTH];
};
} // namespace pb
