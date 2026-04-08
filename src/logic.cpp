#include "sensors.h"
#include "motors.h"
#include "servo_control.h"
#include "config.h"

void runObstacleMode()
{
    float dist = getDistance();

    if (dist >= OBSTACLE_DISTANCE)
    {
        forward();
        return;
    }

    stopMotors();

    lookLeft();
    delay(200);
    float leftDist = getDistance();

    lookRight();
    delay(200);
    float rightDist = getDistance();

    lookCenter();
    delay(100);

    if (leftDist > rightDist)
    {
        left();
    }
    else
    {
        right();
    }

    delay(400);
}