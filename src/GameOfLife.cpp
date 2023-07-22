#include "../include/GameOfLife.h"
#include <array>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

GameOfLife::~GameOfLife()
{
}
GameOfLife::GameOfLife()
{
    m_isPaused = true;

    m_isMouseHeld = false;
    m_isSpaceHeld = false;
    m_isRHeld = false;
    m_isCHeld = false;
    m_isFHeld = false;
    m_isRightHeld = false;
    m_isLeftHeld = false;

    m_changeColor = false;

    initColors();
    initText();

    initGrid();
    initStartingLives();
    

}
void GameOfLife::joinSimThread()
{
    m_simThread.join();

}

void GameOfLife::initColors()
{
    m_colorMagenta = sf::Color::Magenta;
    m_colorRed = sf::Color::Red;
    m_colorTimer = COLOR_TIMER_DEFAULT;
    m_currentColorInt = 0;

    m_aliveCell.setFillColor(sf::Color::Magenta);
    m_aliveCell.setOutlineThickness(1);
    m_aliveCell.setOutlineColor(sf::Color::Black);
}

void GameOfLife::initText()
{
    if(!m_font.loadFromFile("../res/fonts/open-sans/OpenSans-Semibold.ttf"))
        std::cerr << "ERROR::GAMEOFLIFE::INITEXT:: error loading font from file" << '\n';

    m_numberOfLiveCellsText.setFont(m_font);
    m_numberOfLiveCellsText.setCharacterSize(20);
    m_numberOfLiveCellsText.setFillColor(sf::Color::White);
    m_numberOfLiveCellsText.setPosition(10,10);
    m_numberOfLiveCellsText.setString("NULL");

    m_noLiveCells = 0;

}

void GameOfLife::updateText()
{
    long unsigned int temp = 0;
    for(int x = 0; x < m_mapSizeX; ++x)
    {
        for(int y = 0; y < m_mapSizeY; ++y)
        {
            if((*m_currentMap)[x][y] == 1)
            {
                temp ++;
            }
        }
    }
    
    m_noLiveCells = temp;
    
    std::string pauseText = m_isPaused ? "TRUE" : "FALSE";
    std::string colorText = m_changeColor ? "TRUE" : "FALSE";

    std::stringstream ss;
    ss << "LIVE CELLS: " << m_noLiveCells << '\n'
        << "PAUSED: " << pauseText << '\n'
        << "CYCLE COLOR: " << colorText << '\n'
        << "SIMULATION DELAY: " << m_simDelay << '\n'
        ;
    m_numberOfLiveCellsText.setString(ss.str());
}

void GameOfLife::initGrid()
{
    //m_mapSize = MAP_SIZE;
    m_gridSizeF = 8.f;
    m_gridSizeU = static_cast<unsigned>(m_gridSizeF);

    m_currentMap = new std::array<std::array<int, m_mapSizeY>, m_mapSizeX>;
    m_swapMap = new std::array<std::array<int, m_mapSizeY>, m_mapSizeX>;


    m_aliveCell.setSize(sf::Vector2f(m_gridSizeF - m_aliveCell.getOutlineThickness(), m_gridSizeF - m_aliveCell.getOutlineThickness()));
    m_aliveCell.setFillColor(m_currentColor);


    for(long unsigned int x = 0; x < m_mapSizeX; x++)
    {
        for(long unsigned int y = 0; y < m_mapSizeY; y++)
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

void GameOfLife::updateColor(float deltaTime)
{
    if(m_changeColor)
    {
        m_colorTimer -= deltaTime;
        if(m_colorTimer < 0)
        {
            if(m_currentColorInt < 6)
            {
                m_currentColorInt ++;
            }
            else{
                m_currentColorInt = 0;
            }
            m_colorTimer = COLOR_TIMER_DEFAULT;
        }

    }
    else{
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if(!m_isRightHeld)
            {
                m_isRightHeld = true;
                if(m_currentColorInt < 6)
                    m_currentColorInt++;
                else
                    m_currentColorInt = 0;
            }
        }
        else{
            m_isRightHeld = false;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if(!m_isLeftHeld)
            {
                m_isLeftHeld = true;
                if(m_currentColorInt >-1)
                    m_currentColorInt--;
                else
                    m_currentColorInt = 6;
            }
        }
        else{
            m_isLeftHeld = false;
        }
    }


    switch(m_currentColorInt)
    {
        case Colors::RED:
            m_currentColor = sf::Color::Red;
            break;
        case Colors::MAGENTA:
            m_currentColor = sf::Color::Magenta;
            break;
        case Colors::PINK:
            m_currentColor = sf::Color(255,3,255);
            break;
        case Colors::ORANGE:
            m_currentColor = sf::Color(255,128,0);
            break;
        case Colors::YELLOW:
            m_currentColor = sf::Color(255,255,51);
            break;
        case Colors::GREEN:
            m_currentColor = sf::Color::Green;
            break;
        case Colors::BLUE:
            m_currentColor = sf::Color(0,255,255);
            break;
        default:
            break;
    }
    m_aliveCell.setFillColor(m_currentColor);


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

    for(long unsigned int x = 0; x < m_mapSizeX; x++)
    {
        for(long unsigned int y = 0; y < m_mapSizeY; y++)
        {
            if((*m_currentMap)[x][y] == 1)
            {
                m_aliveCell.setPosition(x * m_gridSizeF,y * m_gridSizeF );
                target.draw(m_aliveCell);

            }
        }
    }

    target.draw(m_tileSelector);
    target.draw(m_numberOfLiveCellsText);
}

void GameOfLife::getInput()
{
    if(m_isPaused)
    {
        // SPAWN NEW LIFE
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
                (*m_currentMap)[m_mousePosGrid.x][m_mousePosGrid.y] = 1;
        }
        // DEAD
        if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
                (*m_currentMap)[m_mousePosGrid.x][m_mousePosGrid.y] = 0;
        }

        // REFRESH
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            for(auto &row : *m_currentMap)
            {
                std::generate(row.begin(), row.end(), []() {return rand() % 10 == 0 ? 1 : 0;});
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
        {
            if(!m_isCHeld)
            {
                m_isCHeld = true;
                for(long unsigned int x = 0; x < m_mapSizeX; x++)
                {
                    for(long unsigned int y = 0; y < m_mapSizeY; y++)
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

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
    {
        if(!m_isFHeld)
        {
            m_isFHeld = true;
            m_changeColor = !m_changeColor;
        }
    }else
    {
        m_isFHeld = false;
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

void GameOfLife::startSimThread()
{
    m_simThread = std::thread(&GameOfLife::simulate, this);

}

void GameOfLife::update(float deltaTime,int delaySim)
{

    m_simDelay = delaySim;
    updateMousePos();
    m_tileSelector.setPosition(m_mousePosGrid.x * m_gridSizeF, m_mousePosGrid.y * m_gridSizeF);
    if(m_window->hasFocus())
        getInput();
    updateText();
    

    updateColor(deltaTime);



    


}

void GameOfLife::simulate()
{
    while(m_window->isOpen())
    {
        if(!m_isPaused)
        {

            usleep(m_simDelay);
            for(long unsigned int x = 0; x < m_mapSizeX; x++)
            {
                for(long unsigned int y = 0; y < m_mapSizeY; y++)
                {
                    (*m_swapMap)[x][y] = isAlive(*m_currentMap,x,y) ? 1 : 0;
                }
            }
            std::copy(m_swapMap->begin(), m_swapMap->end(), m_currentMap->begin());
        }

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

bool GameOfLife::isAlive(std::array<std::array<int, m_mapSizeY>, m_mapSizeX> &currentMap, const int &x,const int &y)
{

    
    m_neighbourNumbers = 0;

    //test left
    if(x > 0 && currentMap[x-1][y] == 1)
        m_neighbourNumbers +=1;
    // RIGHT
    if(x < m_mapSizeX  && currentMap[x+1][y] == 1)
        m_neighbourNumbers+= 1;

    //BELOW
    if(y < m_mapSizeY - 1 && currentMap[x][y+1] == 1)
        m_neighbourNumbers +=1;

    // ABOVE
    if(y > 0 && currentMap[x][y-1] == 1)
        m_neighbourNumbers +=1;


    if(y > 0 && x > 0 && currentMap[x-1][y-1] == 1)
        m_neighbourNumbers +=1;

    if(y > 0 && x < m_mapSizeX && currentMap[x+1][y-1] == 1)
        m_neighbourNumbers +=1;
    
    if(y < m_mapSizeY && x > 0 && currentMap[x-1][y+1] == 1)
        m_neighbourNumbers+=1;

    if(y < m_mapSizeY && x < m_mapSizeX && currentMap[x+1][y+1] == 1)
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

