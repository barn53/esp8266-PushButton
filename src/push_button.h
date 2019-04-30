#pragma once
#include <Arduino.h>

namespace pb {
class PushButton {

    static const uint8_t SEQUENCE_LENGTH = 4;
    static const uint8_t DEBOUNCE_MILLIS = 100;

public:
    enum class Event : uint8_t {
        NONE,
        SHORT_PRESS,
        LONG_HOLD,
        DOUBLE_PRESS
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
    uint8_t m_sequence;
    uint8_t m_expected_interrupt_edge;

    volatile uint8_t m_debounced_sequence[SEQUENCE_LENGTH];
    volatile uint32_t m_sequence_timer[SEQUENCE_LENGTH];
};
} // namespace pb
