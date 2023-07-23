#ifndef GAME_H
#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <thread>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "GameOfLife.h"
#include "SFML/Graphics/RenderTarget.hpp"

#include "../include/Time.h"



class Game
{
    private:
        sf::RenderWindow* m_window;
        sf::VideoMode m_videoMode;

        sf::View m_view;
        float m_viewMoveSpeed;


        sf::Event m_event;
        sf::Cursor m_cursor;

        int m_simDelay;

        float m_scrollAmount;

        // Screen Info
        int m_screenWidth;
        int m_screenHeight;

        void initVariables();
        void initWindow();
        void initFont();
        void initText();
        void initGrid();
        void initBoundaries();

        // FONT
        sf::Font m_mainFont;

        std::thread m_renderThread;

        GameOfLife m_gameOfLife;


        // MOUSE POS
        sf::Vector2i m_mousePosScreen;
        sf::Vector2i m_mousePosWindow;
        sf::Vector2f m_mousePosView;
        sf::Vector2u m_mousePosGrid;
        float m_gridSizeF;

        // BOUNDARIES
        sf::RectangleShape m_boundaryLeft;
        sf::RectangleShape m_boundaryRight;
        sf::RectangleShape m_boundaryUp;
        sf::RectangleShape m_boundaryDown;

    public:
        Game();
        virtual ~Game();

        void startGLoop();

        void update();
        void updateTileSelector();
        void updateMousePos();

        void pollEvents();
        void getInput();

        void render();
        void renderBoundaries(sf::RenderTarget &target);


        const bool isRunning() const;

        const int WINDOW_WIDTH;
        const int WINDOW_HEIGHT;

        // Accessors
        sf::RenderWindow* getWindow();


};


#endif
