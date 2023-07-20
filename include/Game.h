#include "GameOfLife.h"
#ifndef GAME_H
#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <thread>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "../include/Time.h"



class Game
{
    private:
        sf::RenderWindow* m_window;
        sf::VideoMode m_videoMode;

        sf::Event m_event;
        sf::Cursor m_cursor;

        int m_simDelay;



        // Screen Info
        int m_screenWidth;
        int m_screenHeight;

        void initVariables();
        void initWindow();
        void initFont();
        void initText();
        void initGrid();

        // FONT
        sf::Font m_mainFont;

        std::thread m_renderThread;

        GameOfLife m_gameOfLife;


    public:
        Game();
        virtual ~Game();

        void startGLoop();

        void update();

        void pollEvents();
        void getInput();

        void render();


        const bool isRunning() const;

        const int WINDOW_WIDTH;
        const int WINDOW_HEIGHT;

        // Accessors
        sf::RenderWindow* getWindow();


};


#endif
