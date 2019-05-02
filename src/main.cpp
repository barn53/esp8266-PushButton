#include <Arduino.h>
#include <Ticker.h>

#include "push_button.h"

using pb::PushButton;

PushButton pb7(D7);
PushButton pb5(D5, RISING);

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
        Serial.println("D7 PushButton::Event::SHORT_PRESS");
        break;
    case PushButton::Event::LONG_PRESS:
        Serial.println("D7 PushButton::Event::LONG_PRESS");
        break;
    case PushButton::Event::LONG_HOLD:
        Serial.println("D7 PushButton::Event::LONG_HOLD");
        break;
    case PushButton::Event::DOUBLE_PRESS:
        Serial.println("D7 PushButton::Event::DOUBLE_PRESS");
        break;
    case PushButton::Event::TRIPLE_PRESS:
        Serial.println("D7 PushButton::Event::TRIPLE_PRESS");
        break;
    case PushButton::Event::NOT_READY:
        //Serial.println("D7 PushButton::Event::NOT_READY");
        break;
    case PushButton::Event::INVALID:
        Serial.println("D7 PushButton::Event::INVALID");
        break;
    default:
        //Serial.println("D7 PushButton::Event::NONE");
        break;
    }
    switch (pb5.getEvent()) {
    case PushButton::Event::SHORT_PRESS:
        Serial.println("D5 PushButton::Event::SHORT_PRESS");
        break;
    case PushButton::Event::LONG_PRESS:
        Serial.println("D5 PushButton::Event::LONG_PRESS");
        break;
    case PushButton::Event::LONG_HOLD:
        Serial.println("D5 PushButton::Event::LONG_HOLD");
        break;
    case PushButton::Event::DOUBLE_PRESS:
        Serial.println("D5 PushButton::Event::DOUBLE_PRESS");
        break;
    case PushButton::Event::TRIPLE_PRESS:
        Serial.println("D5 PushButton::Event::TRIPLE_PRESS");
        break;
    case PushButton::Event::NOT_READY:
        //Serial.println("D5 PushButton::Event::NOT_READY");
        break;
    case PushButton::Event::INVALID:
        Serial.println("D5 PushButton::Event::INVALID");
        break;
    default:
        //Serial.println("D5 PushButton::Event::NONE");
        break;
    }
}
