# esp8266-PushButton
## Arduino library that provides debounced push button functionality on GPIO pins.
### Tested only on ESP8266

One class instance per pin

### Provide the following events:
- short press
- long press
- long hold
- double press
- triple press

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
