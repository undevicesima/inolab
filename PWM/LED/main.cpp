//
// Created by nitsche on 26.05.2026.
//

#include <Arduino.h>
#include <stdint.h>

#if 0
// PWM-enabled pin with LED
constexpr uint8_t PIN_LED = 3;

// Current fading level (Brightness 0..255)
uint8_t fadeLevel = 0;

void setup() {
    // Set Pin as output
    pinMode(PIN_LED, OUTPUT);
}

void loop() {
    // Output fading level as PWM
    analogWrite(PIN_LED, fadeLevel);

    // Increase fade level and reset cleanly to 0 when exceeding 255
    fadeLevel = (fadeLevel < 255) ? fadeLevel + 5 : 0;

    delay(50);
}
#endif
