#include <algorithm>
#include <cstdlib>
#include<iostream>
#include <filesystem>
#include<SFML/Graphics.hpp>

#include "../include/Game.h"


int main(int argc, char* argv[])
{
    std::cout << std::filesystem::current_path();

    std::srand(static_cast<unsigned>(time(NULL)));
    Game game;

    return 0;
}
