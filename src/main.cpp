#include <cstdlib>
#include<iostream>
#include<SFML/Graphics.hpp>

#include "../include/Game.h"

sf::RenderWindow IGNORE(sf::VideoMode(1,1), "IGNORE", sf::Style::Close);

int main()
{
    std::srand(static_cast<unsigned>(time(NULL)));
    Game game;

    return 0;
}
