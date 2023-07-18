
#include "../include/Time.h"

void Time::initDeltaTime()
{
    Time::deltaTime = Time::clock.restart().asSeconds() * Time::MULTIPLIER;
}
