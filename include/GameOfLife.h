#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#pragma once

#include <array>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <thread>
#include <sstream>

#include "Global.h"

const int m_mapSizeX = MAP_SIZE_X;
const int m_mapSizeY = MAP_SIZE_Y;

enum Colors
{
    RED = 0,
    MAGENTA = 1,
    PINK = 2,
    ORANGE = 3,
    YELLOW = 4,
    GREEN = 5,
    BLUE = 6
};
class GameOfLife
{
    private:
        void initGrid();
        void initStartingLives();
        void initText();
        void initColors();

        // GRID
        float m_gridSizeF;
        unsigned m_gridSizeU;
        sf::Text m_gridText;
        
        sf::RectangleShape m_aliveCell;

        std::array<std::array<int, m_mapSizeY>, m_mapSizeX>* m_currentMap;
        std::array<std::array<int, m_mapSizeY>, m_mapSizeX>* m_swapMap;
        


        sf::RenderWindow* m_window;

        // updateMousePos
        sf::Vector2i m_mousePosScreen;
        sf::Vector2i m_mousePosWindow;
        sf::Vector2f m_mousePosView;
        sf::Vector2u m_mousePosGrid;

        std::thread m_simThread;


        bool m_isMouseHeld;
        bool m_isSpaceHeld;
        bool m_isPaused;
        bool m_isRHeld;
        bool m_isCHeld;
        bool m_isFHeld;

        int m_neighbourNumbers;

        sf::RectangleShape m_tileSelector;

        // UI
        sf::Font m_font;
        sf::Text m_numberOfLiveCellsText;
        long unsigned int m_noLiveCells;

        //color changing
        bool m_changeColor;
        sf::Color m_colorMagenta;
        sf::Color m_colorRed;
        int m_currentColorInt;
        sf::Color m_currentColor;
        float m_colorTimer;
        
        int m_simDelay;

    public:
        GameOfLife();
        virtual ~GameOfLife();

        void update(float deltaTime, int delaySim);
        void updateColor(float deltaTime);
        void updateMousePos();
        void updateText();

        void getInput();

        void startSimThread();
        void joinSimThread();

        void render(sf::RenderTarget &target);
        void setWindow(sf::RenderWindow &window);
        float getGridSizeF();

        sf::Vector2u getMouseGrid();

        void simulate();
        void checkHorizontal(int x, int y);
        void checkVertical(int x, int y);
        void checkDiagnonal(int x, int y);

        bool isAlive(std::array<std::array<int, m_mapSizeY>, m_mapSizeX> &currentMap,const int &x,const int &y);
        
};


#endif // !DEBUG
