#include <FunctionalInterrupt.h>
#include <Ticker.h>

#include "push_button.h"

PushButton::PushButton(uint8_t pin)
    : m_pin(pin)
{
    noInterrupts();
    m_counter = 0;
    pinMode(m_pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(m_pin), std::bind(&PushButton::handleInterrupt, this), RISING);
    interrupts();
}

void PushButton::handleInterrupt()
{
    noInterrupts();
    Ticker t;
    t.once_ms(100, []() {
        interrupts();
    });

    ++m_counter;
}
