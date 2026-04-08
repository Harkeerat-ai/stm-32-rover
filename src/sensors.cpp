#include <Arduino.h>
#include "config.h"

float prev = 0;

float ema(float val)
{
    if (prev == 0)
        prev = val;
    float alpha = 0.6;
    float filtered = alpha * prev + (1 - alpha) * val;
    prev = filtered;
    return filtered;
}

void initSensors()
{
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
}

float getDistance()
{
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH);
    float dist = duration * 0.034 / 2;

    return ema(dist);
}