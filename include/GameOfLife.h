#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include <array>
#pragma once

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <thread>



const int m_mapSize = 300;
class GameOfLife
{
    private:
        void initGrid();
        void initStartingLives();

        // GRID
        float m_gridSizeF;
        unsigned m_gridSizeU;
        sf::Text m_gridText;
        
        sf::RectangleShape m_gridShape;

        std::array<std::array<int, m_mapSize>, m_mapSize>* m_currentMap;
        std::array<std::array<int, m_mapSize>, m_mapSize>* m_swapMap;
        std::array<std::array<sf::RectangleShape, m_mapSize>, m_mapSize>* m_shapeMap;

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

        int m_neighbourNumbers;
        

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
