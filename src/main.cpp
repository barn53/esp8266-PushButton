#include <Arduino.h>
#include <Ticker.h>

#include "push_button.h"

using pb::PushButton;

PushButton pb7(D7);

void setup()
{
    Serial.begin(115200);
    delay(500);

    Serial.println("Go!\n");
}

void loop()
{
    switch (pb7.getEvent()) {
    case PushButton::Event::SHORT_PRESS:
        Serial.println("PushButton::Event::SHORT_PRESS");
        break;
    case PushButton::Event::LONG_HOLD:
        Serial.println("PushButton::Event::LONG_HOLD");
        break;
    case PushButton::Event::DOUBLE_PRESS:
        Serial.println("PushButton::Event::DOUBLE_PRESS");
        break;
    case PushButton::Event::NOT_READY:
        //Serial.println("PushButton::Event::NOT_READY");
        break;
    case PushButton::Event::INVALID:
        Serial.println("PushButton::Event::INVALID");
        break;
    default:
        //Serial.println("PushButton::Event::NONE");
        break;
    }
}
