#include "../include/GameOfLife.h"
#include <iostream>
#include <vector>

GameOfLife::GameOfLife()
{
    m_isMouseHeld = false;
    m_isSpaceHeld = false;
    m_isPaused = true;


    initGrid();
    initStartingLives();
    

}
GameOfLife::~GameOfLife()
{
}

void GameOfLife::initGrid()
{
    m_mapSize = 100;
    m_gridSizeF = 10.f;
    m_gridSizeU = static_cast<unsigned>(m_gridSizeF);

    m_currentMap.resize(m_mapSize, std::vector<unsigned int>());
    for(int x = 0; x < m_mapSize; x++)
    {
        m_currentMap[x].resize(m_mapSize, int());
        for(int y = 0; y < m_mapSize; y++)
        {
            m_currentMap[x][y] = 0;
        }
    }

    m_swapMap.resize(m_mapSize, std::vector<unsigned int>());
    for(int x = 0; x<m_mapSize; x++)
    {
        m_swapMap[x].resize(m_mapSize, int());
        for(int y = 0; y < m_mapSize; y++)
        {
            m_swapMap[x][y] = m_currentMap[x][y];
        }
    }



    m_shapeMap.resize(m_mapSize, std::vector<sf::RectangleShape>());
    for(int x = 0; x<m_mapSize; x++)
    {
        m_shapeMap[x].resize(m_mapSize, sf::RectangleShape());
        for(int y = 0; y < m_mapSize; y++)
        {
            m_shapeMap[x][y].setSize(sf::Vector2f(m_gridSizeF,m_gridSizeF));
            m_shapeMap[x][y].setFillColor(sf::Color::Black);
            m_shapeMap[x][y].setPosition(x * m_gridSizeF, y * m_gridSizeF);
            m_shapeMap[x][y].setOutlineThickness(0.3f);
            m_shapeMap[x][y].setOutlineColor(sf::Color::White);
        }
    }

}

void GameOfLife::initStartingLives()
{
    for(auto &row : m_currentMap)
    {
        std::generate(row.begin(), row.end(), []() {return rand() % 10 == 0 ? 1 : 0;});
    }

    for(int x = 0; x < m_mapSize; x++)
    {
        for(int y = 0; y < m_mapSize; y++)
        {
            if(m_currentMap[x][y] == 1)
            {
                m_shapeMap[x][y].setFillColor(sf::Color::White);
                m_shapeMap[x][y].setOutlineColor(sf::Color::Black);
            }
        }
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

    for(int x = 0; x < m_mapSize; x++)
    {
        for(int y = 0; y < m_mapSize; y++)
        {
            target.draw(m_shapeMap[x][y]);
        }
    }
}

void GameOfLife::getInput()
{
    if(m_isPaused)
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if(!m_isMouseHeld)
            {
                m_isMouseHeld = true;
                if(m_currentMap[m_mousePosGrid.x][m_mousePosGrid.y] == 0)
                {
                    m_currentMap[m_mousePosGrid.x][m_mousePosGrid.y] = 1;
                }
                else{

                    m_currentMap[m_mousePosGrid.x][m_mousePosGrid.y] = 0;
                }
            }
        }
        else{
            m_isMouseHeld = false;
        }

        for(int x = 0; x < m_mapSize; x++)
        {
            for(int y = 0; y < m_mapSize; y++)
            {
                if(m_currentMap[x][y] == 1)
                {
                    m_shapeMap[x][y].setFillColor(sf::Color::White);
                    m_shapeMap[x][y].setOutlineColor(sf::Color::Black);
                }
                else{
                    m_shapeMap[x][y].setFillColor(sf::Color::Black);
                    m_shapeMap[x][y].setOutlineColor(sf::Color::White);
                }
            }
        }
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
    getInput();
    updateMousePos();
    //simulate();



    if(!m_isPaused )
    {
        //THREAD LATER
        m_simThread = std::thread(&GameOfLife::simulate, this, delaySim);
        m_simThread.join();
    }
    


}

void GameOfLife::simulate(int delaySim)
{
    usleep(5000);
    for(int x = 0; x < m_mapSize; x++)
    {
        for(int y = 0; y < m_mapSize; y++)
        {
            m_swapMap[x][y] = isAlive(m_currentMap,x,y) ? 1 : 0;
        }
    }
    for(int x = 0; x < m_mapSize; x++)
    {
        for(int y = 0; y < m_mapSize; y++)
        {
            if(m_swapMap[x][y] == 1)
            {
                m_shapeMap[x][y].setFillColor(sf::Color::White);
                m_shapeMap[x][y].setOutlineColor(sf::Color::Black);
            }
            else{
                m_shapeMap[x][y].setFillColor(sf::Color::Black);
                m_shapeMap[x][y].setOutlineColor(sf::Color::White);
            }
        }
    }
    std::copy(m_swapMap.begin(), m_swapMap.end(), m_currentMap.begin());
}

/*
void GameOfLife::checkHorizontal(int x, int y)
{

    // HORIZONTAL CHECKS
    // RIGHT
    if(x < m_mapSize  && m_map[x+1][y].m_state == 1)
    {
        m_neighbourNumbers++;
    }
    //LEFT
    if(x > 0 && m_map[x-1][y].m_state == 1)
    {
        m_neighbourNumbers++;
    }


}

void GameOfLife::checkVertical(int x, int y)
{


    //VERTICAL
    //BELOW
    if(y < m_mapSize - 1 && m_map[x][y+1].m_state == 1)
    {
        m_neighbourNumbers ++;
    }

    // ABOVE
    if(y > 0 && m_map[x][y-1].m_state == 1)
    {
        m_neighbourNumbers ++;
    }

}

void GameOfLife::checkDiagnonal(int x, int y)
{

    // DIAGONAL
    // Top right
    if(x < m_mapSize && y < m_mapSize - 1 && m_map[x+1][y+1].m_state == 1)
    {
        m_neighbourNumbers ++;
    }
    if(x > 0 && y < m_mapSize - 1 && m_map[x-1][y+1].m_state == 1)
    {
        m_neighbourNumbers ++;
    }

    if(x < m_mapSize && y > 0 && m_map[x+1][y-1].m_state == 1 )
    {
        m_neighbourNumbers ++;
    }
    if(x > 0 && y > 0 && m_map[x-1][y-1].m_state == 1)
    {
        m_neighbourNumbers ++;
    }
}
*/

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

bool GameOfLife::isAlive(std::vector<std::vector<unsigned int>> &currentMap, const int x,const int y)
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

