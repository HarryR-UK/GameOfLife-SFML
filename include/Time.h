#ifndef TIME_H
#pragma once

#include <SFML/System/Clock.hpp>
#include "../include/Time.h"
#include "Global.h"

class Time{
    public:
        inline static sf::Clock clock;
        inline static float deltaTime;
        static void initDeltaTime();
        
    private:
        static constexpr float MULTIPLIER = TIME_DELTATIME_MULT;;

};

#endif // !TIME_H
