#include <FunctionalInterrupt.h>

#include "push_button.h"

namespace pb {
void PushButton::attach()
{
    attachInterrupt(digitalPinToInterrupt(m_pin), std::bind(&PushButton::handleInterrupt, this), m_expected_interrupt_edge);
}

void PushButton::detach()
{
    detachInterrupt(digitalPinToInterrupt(m_pin));
}

void PushButton::reset()
{
    m_sequence = 0;
    m_expected_interrupt_edge = m_initial_edge;

    for (uint8_t ii = 0; ii < SEQUENCE_LENGTH; ++ii) {
        m_sequence_timer[ii] = 0;
    }

    pinMode(m_pin, m_initial_edge == FALLING ? INPUT_PULLUP : INPUT);
}

void PushButton::handleInterrupt()
{
    detach();

    if (m_sequence >= SEQUENCE_LENGTH) {
        reset();
    }

    if (m_sequence < SEQUENCE_LENGTH) {
        m_sequence_timer[m_sequence] = (m_sequence == 0
                ? millis()
                : millis() - m_sequence_timer[0]);
    }
    ++m_sequence;

    // for (uint8_t ii = 0; ii < SEQUENCE_LENGTH; ++ii) {
    //     Serial.printf("m_sequence_timer[%d]: %d\n", ii, m_sequence_timer[ii]);
    // }

    m_expected_interrupt_edge = (m_expected_interrupt_edge == FALLING
            ? RISING
            : FALLING);

    if (m_sequence <= SEQUENCE_LENGTH) {
        // debouncing
        m_ticker.once_ms(DEBOUNCE_MILLIS, std::bind(&PushButton::attach, this));
    }
}

///////////////////////////////////////////////////
///////   A P I
///////////////////////////////////////////////////

PushButton::PushButton(uint8_t pin)
    : m_pin(pin)
    , m_initial_edge(FALLING)
{
    reset();
    attach();
}

PushButton::PushButton(uint8_t pin, uint8_t initialEdge)
    : m_pin(pin)
    , m_initial_edge(initialEdge)
{
    reset();
    attach();
}

PushButton::Event PushButton::getEvent()
{
    Event e(Event::NONE);

    if (m_sequence == 2) {
        if (millis() - m_sequence_timer[0] > MAX_MILLIS_SHORT_PRESS) {
            if (m_sequence_timer[1] < MAX_MILLIS_SHORT_PRESS) {
                e = Event::SHORT_PRESS;
            } else if (m_sequence_timer[1] < MAX_MILLIS_LONG_PRESS) {
                e = Event::LONG_PRESS;
            } else if (m_sequence_timer[1] < MAX_MILLIS_LONG_HOLD) {
                e = Event::LONG_HOLD;
            } else {
                e = Event::INVALID;
            }
            reset();
        } else {
            e = Event::NOT_READY;
        }
    } else if (m_sequence == 4) {
        if (millis() - m_sequence_timer[0] > MAX_MILLIS_MULTI_PRESS_GAP * 3) {
            if (m_sequence_timer[1] < MAX_MILLIS_MULTI_PRESS_GAP
                && m_sequence_timer[2] < MAX_MILLIS_MULTI_PRESS_GAP * 2
                && m_sequence_timer[3] < MAX_MILLIS_MULTI_PRESS_GAP * 3) {
                e = Event::DOUBLE_PRESS;
            } else {
                e = Event::INVALID;
            }
            reset();
        } else {
            e = Event::NOT_READY;
        }
    } else if (m_sequence == 6) {
        if (m_sequence_timer[1] < MAX_MILLIS_MULTI_PRESS_GAP
            && m_sequence_timer[2] < MAX_MILLIS_MULTI_PRESS_GAP * 2
            && m_sequence_timer[3] < MAX_MILLIS_MULTI_PRESS_GAP * 3
            && m_sequence_timer[4] < MAX_MILLIS_MULTI_PRESS_GAP * 4
            && m_sequence_timer[5] < MAX_MILLIS_MULTI_PRESS_GAP * 5) {
            e = Event::TRIPLE_PRESS;
        } else {
            e = Event::INVALID;
        }
        reset();
    }

    return e;
}
} // namespace pb
