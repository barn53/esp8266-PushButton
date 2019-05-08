[![Build Status](https://travis-ci.org/gerdmuller/esp8266-PushButton.svg?branch=master)](https://travis-ci.org/gerdmuller/esp8266-PushButton)

# esp8266-PushButton
## Arduino library that provides debounced push button functionality on GPIO pins.

### Provide the following events:
- short press
- long press
- long hold
- double press
- triple press

One class instance per pin.

Tested only on ESP8266.

### Usage:
````
#include <Arduino.h>
#include <push_button.h>
...
pb::PushButton button(D1);
...
void loop()
{
    switch (button.getEvent()) {
    case pb::PushButton::Event::SHORT_PRESS:
        // action for short press
        break;
    case pb::PushButton::Event::DOUBLE_PRESS:
        // action for double press
        break;
    ...
}
````
