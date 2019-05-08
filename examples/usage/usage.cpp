#include "push_button.h"

using pb::PushButton;

PushButton button(D7);

void setup()
{
    Serial.begin(115200);
    delay(500);
    Serial.println("Go!\n");
}

void loop()
{
    switch (button.getEvent()) {
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
}
