#include <FunctionalInterrupt.h>
#include <Ticker.h>

#include "push_button.h"

namespace {
void attach_wrapper(uint32_t pb)
{
    auto pushButton(reinterpret_cast<pb::PushButton*>(pb));
    pushButton->attach();
}
}

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
    detach();
    m_sequence = 0;
    m_expected_interrupt_edge = m_initial_edge;

    for (uint8_t ii = 0; ii < SEQUENCE_LENGTH; ++ii) {
        m_debounced_sequence[ii] = 0;
        m_sequence_timer[ii] = 0;
    }

    pinMode(m_pin, m_initial_edge == FALLING ? INPUT_PULLUP : INPUT);
    attach();
}

void PushButton::handleInterrupt()
{
    detach();

    if (m_sequence < SEQUENCE_LENGTH) {
        m_debounced_sequence[m_sequence] = m_expected_interrupt_edge;
        m_sequence_timer[m_sequence] = (m_sequence == 0
                ? millis()
                : millis() - m_sequence_timer[0]);
    }
    ++m_sequence;

    m_expected_interrupt_edge = (m_expected_interrupt_edge == FALLING
            ? RISING
            : FALLING);

    if (m_sequence <= SEQUENCE_LENGTH) {
        // debouncing
        Ticker t;
        t.once_ms(DEBOUNCE_MILLIS, attach_wrapper, reinterpret_cast<uint32_t>(this));
    } else {
        reset();
    }
}

///////////////////////////////////////////////////
///////   A P I
///////////////////////////////////////////////////

PushButton::PushButton(uint8_t pin)
    : m_pin(pin)
    , m_initial_edge(FALLING)
{
    interrupts();
    reset();
}

PushButton::PushButton(uint8_t pin, uint8_t initialEdge)
    : m_pin(pin)
    , m_initial_edge(initialEdge)
{
    interrupts();
    reset();
}

PushButton::Event PushButton::getEvent()
{
    detach();

    Event e(Event::NONE);
    if (m_sequence == 2) {
        if (m_sequence_timer[1] < 1000) {
            e = Event::SHORT_PRESS;
        } else if (m_sequence_timer[1] < 2000) {
            e = Event::LONG_HOLD;
        } else { // invalid sequence
            reset();
        }
    } else if (m_sequence == 4) {
        if (m_sequence_timer[1] < 1000
            && m_sequence_timer[2] < 1000
            && m_sequence_timer[3] < 1000) {
            e = Event::DOUBLE_PRESS;
        } else { // invalid sequence
            reset();
        }
    }

    attach();
    return e;
}
} // namespace pb
