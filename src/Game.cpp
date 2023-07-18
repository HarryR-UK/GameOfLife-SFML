#include "../include/Game.h"
#include <vector>

const bool Game::isRunning() const
{
    return m_window->isOpen();
}

Game::~Game()
{
    delete m_window;
}


Game::Game()
    : WINDOW_WIDTH(sf::VideoMode::getDesktopMode().width / 1), 
    WINDOW_HEIGHT(sf::VideoMode::getDesktopMode().height / 1),
    m_gameOfLife()
{
    initVariables();
    initWindow();
    initFont();
    initText();

    m_gameOfLife.setWindow(*m_window);

    m_tileSelector.setSize(sf::Vector2f(m_gameOfLife.getGridSizeF(), m_gameOfLife.getGridSizeF()));
    m_tileSelector.setFillColor(sf::Color::Transparent);
    m_tileSelector.setOutlineThickness(1.f);
    m_tileSelector.setOutlineColor(sf::Color::Red);

    startGLoop();
}


void Game::initVariables()
{
    m_window = nullptr;
    

    m_screenWidth = sf::VideoMode::getDesktopMode().width;
    m_screenHeight = sf::VideoMode::getDesktopMode().height;


}

void Game::initWindow()
{
    m_videoMode.height = WINDOW_HEIGHT;
    m_videoMode.width = WINDOW_WIDTH;

    m_window = new sf::RenderWindow(m_videoMode, "GAME OF LIFE!", sf::Style::Close | sf::Style::None);
}

void Game::initFont()
{
    if(!m_mainFont.loadFromFile("../res/fonts/open-sans/OpenSans-Regular.ttf"))
    {
        std::cerr << "ERROR::GAME::INITFONT::Failed to load main font" << '\n';
    }
}

void Game::initText()
{

}


void Game::pollEvents()
{
    while(m_window->pollEvent(m_event))
    {
        switch (m_event.type) {
            case sf::Event::Closed:
                m_window->close();
                break;
            default:
                break;
        }
    }
}


void Game::getInput()
{

}

void Game::updateMousePos()
{
    m_mousePosGrid = m_gameOfLife.getMouseGrid();
}

void Game::update()
{
    pollEvents();
    getInput();
    updateMousePos();
    m_tileSelector.setPosition(m_mousePosGrid.x * m_gameOfLife.getGridSizeF(), m_mousePosGrid.y * m_gameOfLife.getGridSizeF());
    
    m_gameOfLife.update(5.f);

}


void Game::render()
{
    m_window->clear();

    m_gameOfLife.render(*this->m_window);

    m_window->draw(m_tileSelector);
    m_window->display();
}

void Game::startGLoop()
{
    while(this->isRunning())
    {
        Time::initDeltaTime();

        this->update();

        this->render();

    }
}
