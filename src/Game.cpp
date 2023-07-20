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
    : WINDOW_WIDTH(sf::VideoMode::getDesktopMode().width / 1.2), 
    WINDOW_HEIGHT(sf::VideoMode::getDesktopMode().height / 1.2),
    m_gameOfLife()
{
    initVariables();
    initWindow();
    initFont();
    initText();

    m_window->setMouseCursorVisible(false);
    m_gameOfLife.setWindow(*m_window);


    startGLoop();

}


void Game::initVariables()
{
    m_simDelay = 55555;
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
            case sf::Event::MouseWheelMoved:
                if(m_simDelay > 0)
                    m_simDelay += 1000 * (m_event.mouseWheel.delta);
                else{
                    m_simDelay = 10;
                }
                break;
            default:
                break;
        }
    }

    if(m_window->hasFocus())
    {
        m_window->setMouseCursorVisible(false);
    }
    else{
        m_window->setMouseCursorVisible(true);
    }
}


void Game::getInput()
{

}


void Game::update()
{
    pollEvents();
    getInput();

    if(m_simDelay < 0){
        m_simDelay = 10;
    }
    
    m_gameOfLife.update(Time::deltaTime,m_simDelay);

}


void Game::render()
{
    while(isRunning())
    {
        m_window->clear();

        m_gameOfLife.render(*this->m_window);


        m_window->display();

    }
}


void Game::startGLoop()
{
    m_gameOfLife.startSimThread();
    m_renderThread = std::thread(&Game::render, this);
    while(this->isRunning())
    {
        Time::initDeltaTime();
        
        this->update();

        
        //this->render();


    }
    m_gameOfLife.joinSimThread();
    m_renderThread.join();
}
