#include <Arduino.h>
#include "sensors.h"
#include "motors.h"
#include "servo_control.h"
#include "logic.h"

void setup()
{
    Serial.begin(115200);

    initSensors();
    initMotors();
    initServo();
}

void loop()
{
    float dist = getDistance();

    runObstacleMode();

    char buffer[50];
    sprintf(buffer, "Distance: %.2f", dist);

    Serial.println(buffer);

    delay(300);
}