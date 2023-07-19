#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#pragma once

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <thread>

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
        int m_mapSize;

        std::vector<std::vector<unsigned int> > m_currentMap;
        std::vector<std::vector<unsigned int> > m_swapMap;
        std::vector<std::vector<sf::RectangleShape>> m_shapeMap;


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

        bool isAlive(std::vector<std::vector<unsigned int>> &currentMap,const int x,const int y);

};


#endif // !DEBUG
