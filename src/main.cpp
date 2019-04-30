#include <Arduino.h>

#include "push_button.h"

using pb::PushButton;

PushButton pb1(D0);
PushButton pb2(D1);

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    switch (pb1.getEvent()) {
    case PushButton::Event::SHORT_PRESS:
        Serial.println("PushButton::Event::SHORT_PRESS");
        break;
    case PushButton::Event::LONG_HOLD:
        Serial.println("PushButton::Event::LONG_HOLD");
        break;
    case PushButton::Event::DOUBLE_PRESS:
        Serial.println("PushButton::Event::DOUBLE_PRESS");
        break;
    default:
        Serial.println("PushButton::Event::NONE");
        break;
    }
}
