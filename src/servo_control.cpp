#include <Arduino.h>
#include <Servo.h>
#include "config.h"
#include "sensors.h"
#include "motors.h"

Servo servo;

#define CENTER_ANGLE 90
#define LEFT_ANGLE 150
#define RIGHT_ANGLE 30

#define STEP_DELAY 10

void initServo()
{
    servo.attach(SERVO_PIN);
    servo.write(CENTER_ANGLE);
    delay(300);
}

void moveSmoothWithScan(int from, int to)
{
    if (from < to)
    {
        for (int i = from; i <= to; i++)
        {
            servo.write(i);

            float dist = getDistance();
            if (dist < OBSTACLE_DISTANCE)
            {
                stopMotors();
            }

            delay(STEP_DELAY);
        }
    }
    else
    {
        for (int i = from; i >= to; i--)
        {
            servo.write(i);

            float dist = getDistance();
            if (dist < OBSTACLE_DISTANCE)
            {
                stopMotors();
            }

            delay(STEP_DELAY);
        }
    }
}

void lookLeft()
{
    moveSmoothWithScan(servo.read(), LEFT_ANGLE);
}

void lookRight()
{
    moveSmoothWithScan(servo.read(), RIGHT_ANGLE);
}

void lookCenter()
{
    moveSmoothWithScan(servo.read(), CENTER_ANGLE);
}