#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include "SFML/Graphics/View.hpp"
#include <memory>
#pragma once

#include <array>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <thread>
#include <sstream>

#include "Global.h"

constexpr int m_mapSizeX = MAP_SIZE_X;
constexpr int m_mapSizeY = MAP_SIZE_Y;

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
        sf::View* m_view;

        // updateMousePos
        sf::Vector2u m_mousePosGrid;

        std::thread m_simThread;


        bool m_isMouseHeld;
        bool m_isSpaceHeld;
        bool m_isPaused;
        bool m_isRHeld;
        bool m_isCHeld;
        bool m_isFHeld;
        bool m_isRightHeld;
        bool m_isLeftHeld;
        bool m_isOHeld;
        bool m_isPixel;

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
        void updateText();
        void updateTileSelector();

        void getInput();

        void startSimThread();
        void joinSimThread();

        void render(sf::RenderTarget &target);
        void renderUI(sf::RenderTarget &target);
        float getGridSizeF();
        sf::Vector2u getMouseGrid();

        void setWindow(sf::RenderWindow &window);
        void setMousePosGrid(sf::Vector2u mousePosGrid);
        void setView(sf::View &view);

        void simulate();

        bool isAlive(std::array<std::array<int, m_mapSizeY>, m_mapSizeX> &currentMap,const int &x,const int &y);
        
};


#endif // !DEBUG
