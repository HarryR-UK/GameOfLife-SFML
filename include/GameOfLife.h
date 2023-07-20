#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include <array>
#pragma once

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <thread>

#include "Global.h"

const int m_mapSize =MAP_SIZE;
class GameOfLife
{
    private:
        void initGrid();
        void initStartingLives();

        // GRID
        float m_gridSizeF;
        unsigned m_gridSizeU;
        sf::Text m_gridText;
        
        sf::RectangleShape m_aliveCell;

        std::array<std::array<int, m_mapSize>, m_mapSize>* m_currentMap;
        std::array<std::array<int, m_mapSize>, m_mapSize>* m_swapMap;
        


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

        int m_neighbourNumbers;

        sf::RectangleShape m_tileSelector;

        // UI
        sf::Font m_font;
        sf::Text m_numberOfLiveCellsText;
        int m_noLiveCells;

        //color changing
        

    public:
        GameOfLife();
        virtual ~GameOfLife();

        void update(float deltaTime,int delaySim);
        void updateMousePos();
        void getInput();

        void render(sf::RenderTarget &target);
        void setWindow(sf::RenderWindow &window);
        float getGridSizeF();

        sf::Vector2u getMouseGrid();

        void simulate(int delaySim);
        void checkHorizontal(int x, int y);
        void checkVertical(int x, int y);
        void checkDiagnonal(int x, int y);

        bool isAlive(std::array<std::array<int, m_mapSize>, m_mapSize> &currentMap,const int &x,const int &y);
        
};


#endif // !DEBUG
