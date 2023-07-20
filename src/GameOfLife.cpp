#include "../include/GameOfLife.h"
#include <array>
#include <iostream>
#include <vector>

GameOfLife::GameOfLife()
{
    m_isMouseHeld = false;
    m_isSpaceHeld = false;
    m_isPaused = true;
    m_isRHeld = false;
    m_isCHeld = false;



    initGrid();
    initStartingLives();
    

}
GameOfLife::~GameOfLife()
{
}



void GameOfLife::initGrid()
{
    //m_mapSize = MAP_SIZE;
    m_gridSizeF = 5.f;
    m_gridSizeU = static_cast<unsigned>(m_gridSizeF);

    m_currentMap = new std::array<std::array<int, m_mapSize>, m_mapSize>;
    m_swapMap = new std::array<std::array<int, m_mapSize>, m_mapSize>;


    m_aliveCell.setSize(sf::Vector2f(m_gridSizeF, m_gridSizeF));
    m_aliveCell.setFillColor(sf::Color::Magenta);


    for(long unsigned int x = 0; x < m_mapSize; x++)
    {
        for(long unsigned int y = 0; y < m_mapSize; y++)
        {
            (*m_currentMap)[x][y] = 0;

        }
    }




    std::copy(m_currentMap->begin(), m_currentMap->end(), m_swapMap->begin());



    m_tileSelector.setSize(sf::Vector2f(m_gridSizeF, m_gridSizeF));
    m_tileSelector.setFillColor(sf::Color::Transparent);
    m_tileSelector.setOutlineThickness(1);
    m_tileSelector.setOutlineColor(sf::Color::Green);

}

void GameOfLife::initStartingLives()
{
    for(auto &row : *m_currentMap)
    {
        std::generate(row.begin(), row.end(), []() {return rand() % 10 == 0 ? 1 : 0;});
    }

}


void GameOfLife::updateMousePos()
{
    m_mousePosScreen = sf::Mouse::getPosition();
    m_mousePosWindow = sf::Mouse::getPosition(*m_window);
    m_mousePosView = m_window->mapPixelToCoords(m_mousePosWindow);

    if(m_mousePosView.x >= 0.f)
        m_mousePosGrid.x = m_mousePosView.x / m_gridSizeU;

    if(m_mousePosView.y >= 0.f)
        m_mousePosGrid.y = m_mousePosView.y / m_gridSizeU;

    

}

void GameOfLife::render(sf::RenderTarget &target)
{

    for(long unsigned int x = 0; x < m_mapSize; x++)
    {
        for(long unsigned int y = 0; y < m_mapSize; y++)
        {
            if((*m_currentMap)[x][y] == 1)
            {
                m_aliveCell.setPosition(x * m_gridSizeF,y * m_gridSizeF );
                target.draw(m_aliveCell);

            }
        }
    }

    target.draw(m_tileSelector);
}

void GameOfLife::getInput()
{
    if(m_isPaused)
    {
        // SPAWN NEW LIFE
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if(!m_isMouseHeld)
            {
                m_isMouseHeld = true;
                if((*m_currentMap)[m_mousePosGrid.x][m_mousePosGrid.y] == 0)
                {
                    (*m_currentMap)[m_mousePosGrid.x][m_mousePosGrid.y] = 1;
                }
                else{

                    (*m_currentMap)[m_mousePosGrid.x][m_mousePosGrid.y] = 0;
                }
            }
        }
        else{
            m_isMouseHeld = false;
        }

        // REFRESH
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            if(!m_isRHeld)
            {
                m_isRHeld = true;

                for(auto &row : *m_currentMap)
                {
                    std::generate(row.begin(), row.end(), []() {return rand() % 10 == 0 ? 1 : 0;});
                }
            }
        }
        else{
            m_isRHeld = false;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
        {
            if(!m_isCHeld)
            {
                m_isCHeld = true;
                for(long unsigned int x = 0; x < m_mapSize; x++)
                {
                    for(long unsigned int y = 0; y < m_mapSize; y++)
                    {
                        (*m_currentMap)[x][y] = 0;
                    }
                }
            }
        }
        else {
            m_isCHeld = false;
        }


        std::copy(m_currentMap->begin(), m_currentMap->end(), m_swapMap->begin());



    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if(!m_isSpaceHeld)
        {
            m_isSpaceHeld = true;
            m_isPaused = !m_isPaused;
        }
    }
    else{
        m_isSpaceHeld = false;
    }
}

void GameOfLife::update(float deltaTime,int delaySim)
{

    m_simThread = std::thread(&GameOfLife::simulate, this, delaySim);
    
    getInput();
    updateMousePos();

    m_tileSelector.setPosition(m_mousePosGrid.x * m_gridSizeF, m_mousePosGrid.y * m_gridSizeF);



    m_simThread.join();

    


}

void GameOfLife::simulate(int delaySim)
{
    if(!m_isPaused)
    {

        usleep(delaySim);
        for(long unsigned int x = 0; x < m_mapSize; x++)
        {
            for(long unsigned int y = 0; y < m_mapSize; y++)
            {
                (*m_swapMap)[x][y] = isAlive(*m_currentMap,x,y) ? 1 : 0;
            }
        }
        std::copy(m_swapMap->begin(), m_swapMap->end(), m_currentMap->begin());
    }


}


void GameOfLife::setWindow(sf::RenderWindow &window)
{
    m_window = &window;
}

float GameOfLife::getGridSizeF()
{
    return m_gridSizeF;
}

sf::Vector2u GameOfLife::getMouseGrid()
{
    return m_mousePosGrid;
}

bool GameOfLife::isAlive(std::array<std::array<int, m_mapSize>, m_mapSize> &currentMap, const int &x,const int &y)
{

    
    m_neighbourNumbers = 0;

    //test left
    if(x > 0 && currentMap[x-1][y] == 1)
        m_neighbourNumbers +=1;
    // RIGHT
    if(x < m_mapSize  && currentMap[x+1][y] == 1)
        m_neighbourNumbers+= 1;

    //BELOW
    if(y < m_mapSize - 1 && currentMap[x][y+1] == 1)
        m_neighbourNumbers +=1;

    // ABOVE
    if(y > 0 && currentMap[x][y-1] == 1)
        m_neighbourNumbers +=1;


    if(y > 0 && x > 0 && currentMap[x-1][y-1] == 1)
        m_neighbourNumbers +=1;

    if(y > 0 && x < m_mapSize && currentMap[x+1][y-1] == 1)
        m_neighbourNumbers +=1;
    
    if(y < m_mapSize && x > 0 && currentMap[x-1][y+1] == 1)
        m_neighbourNumbers+=1;

    if(y < m_mapSize && x < m_mapSize && currentMap[x+1][y+1] == 1)
        m_neighbourNumbers +=1;


    if(currentMap[x][y] == 1 && m_neighbourNumbers < 2)
        return false;

    if(currentMap[x][y] == 1 && (m_neighbourNumbers == 2 || m_neighbourNumbers ==3))
        return true;

    if(m_neighbourNumbers > 3)
        return false;

    if(currentMap[x][y] == 0 && m_neighbourNumbers == 3)
        return true;

    return false;
}

