#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#pragma once

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

struct Cell{
    sf::RectangleShape m_shape;
    int m_state;
};
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

        std::vector<std::vector<Cell>> m_map;


        sf::RenderWindow* m_window;

        // updateMousePos
        sf::Vector2i m_mousePosScreen;
        sf::Vector2i m_mousePosWindow;
        sf::Vector2f m_mousePosView;
        sf::Vector2u m_mousePosGrid;

        float m_simDelay;
        bool m_isHeld;
        bool m_isPaused;
        

    public:
        GameOfLife();
        virtual ~GameOfLife();

        void update(float delaySim);
        void updateMousePos();
        void getInput();

        void render(sf::RenderTarget &target);
        void setWindow(sf::RenderWindow &window);
        float getGridSizeF();
        sf::Vector2u getMouseGrid();

};


#endif // !DEBUG
