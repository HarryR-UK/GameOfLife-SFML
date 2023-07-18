#include "../include/GameOfLife.h"
#include <sys/_types/_wint_t.h>

GameOfLife::GameOfLife()
{
    m_isHeld = false;
    m_isPaused = false;

    initGrid();
    initStartingLives();
    

}
GameOfLife::~GameOfLife()
{
}

void GameOfLife::initGrid()
{
    m_gridSizeF = 20.f;
    m_gridSizeU = static_cast<unsigned>(m_gridSizeF);
    m_mapSize = 50;
    

    m_map.resize(m_mapSize, std::vector<Cell>());
    for(int x = 0; x < m_map.size(); x ++)
    {
        m_map[x].resize(m_mapSize, Cell());
        for(int y = 0; y < m_map.size(); y++)
        {
            m_map[x][y].m_state = 0;
            m_map[x][y].m_shape.setSize(sf::Vector2f(m_gridSizeF,m_gridSizeF));
            m_map[x][y].m_shape.setFillColor(sf::Color::Black);
            m_map[x][y].m_shape.setOutlineThickness(1.f);
            m_map[x][y].m_shape.setOutlineColor(sf::Color::White);
            m_map[x][y].m_shape.setPosition(x * m_gridSizeF, y * m_gridSizeF);
        }
    }

}

void GameOfLife::initStartingLives()
{
    m_map[10][2].m_state = 1;
    m_map[10][2].m_shape.setFillColor(sf::Color::White);
    m_map[10][2].m_shape.setOutlineColor(sf::Color::Black);

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

    for(int x = 0; x < m_map.size(); x++)
    {
        for(int y = 0; y < m_map.size(); y++)
        {
            target.draw(m_map[x][y].m_shape);
        }
    }
}

void GameOfLife::getInput()
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(!m_isHeld)
        {
            m_isHeld = true;
            if(m_map[m_mousePosGrid.x][m_mousePosGrid.y].m_state == 0)
            {
                m_map[m_mousePosGrid.x][m_mousePosGrid.y].m_state = 1;
                m_map[m_mousePosGrid.x][m_mousePosGrid.y].m_shape.setFillColor(sf::Color::White);
                m_map[m_mousePosGrid.x][m_mousePosGrid.y].m_shape.setOutlineColor(sf::Color::Black); 
            }
            else{

                m_map[m_mousePosGrid.x][m_mousePosGrid.y].m_state = 0;
                m_map[m_mousePosGrid.x][m_mousePosGrid.y].m_shape.setFillColor(sf::Color::Black);
                m_map[m_mousePosGrid.x][m_mousePosGrid.y].m_shape.setOutlineColor(sf::Color::White); 
            }
        }
    }
    else{
        m_isHeld = false;
    }
}

void GameOfLife::update(float delaySim)
{
    m_simDelay = delaySim;
    getInput();
    updateMousePos();
    

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
