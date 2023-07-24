#include "../include/Game.h"

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

    m_gridSizeF = m_gameOfLife.getGridSizeF();
    initBoundaries();


    startGLoop();

}


void Game::initVariables()
{
    m_simDelay = 55555;
    m_window = nullptr;
    m_scrollAmount = 1.5;
    

    m_screenWidth = sf::VideoMode::getDesktopMode().width;
    m_screenHeight = sf::VideoMode::getDesktopMode().height;



}

void Game::initBoundaries()
{
    m_boundaryLeft.setSize(sf::Vector2f(10, m_mapSizeY * m_gridSizeF));
    m_boundaryLeft.setPosition(sf::Vector2f(0 - m_boundaryLeft.getSize().x - 1, m_window->getSize().y - m_boundaryLeft.getSize().y));
    m_boundaryLeft.setFillColor(sf::Color(192,192,192));

    m_boundaryRight.setSize(sf::Vector2f(10, m_mapSizeY * m_gridSizeF));
    m_boundaryRight.setPosition(sf::Vector2f(m_mapSizeX * m_gridSizeF + 1, m_window->getSize().y - m_boundaryLeft.getSize().y));
    m_boundaryRight.setFillColor(sf::Color(192,192,192));

    m_boundaryUp.setSize(sf::Vector2f(m_mapSizeX * m_gridSizeF, 10));
    m_boundaryUp.setPosition(sf::Vector2f(0, 0 - m_boundaryUp.getSize().y - 1));
    m_boundaryUp.setFillColor(sf::Color(192,192,192));

    m_boundaryDown.setSize(sf::Vector2f(m_mapSizeX * m_gridSizeF, 10));
    m_boundaryDown.setPosition(sf::Vector2f(0, m_window->getSize().y + 1));
    m_boundaryDown.setFillColor(sf::Color(192,192,192));

}

void Game::initWindow()
{
    m_videoMode.height = WINDOW_HEIGHT;
    m_videoMode.width = WINDOW_WIDTH;

    m_window = new sf::RenderWindow(m_videoMode, "GAME OF LIFE!", sf::Style::Close | sf::Style::None);

    m_view.setSize(m_window->getSize().x, m_window->getSize().y);
    m_view.setCenter(m_window->getSize().x / 2.f, m_window->getSize().y /2.f);
    m_viewMoveSpeed = 20.f;

    m_gameOfLife.setView(m_view);

}

void Game::initFont()
{
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
                if(m_event.mouseWheel.delta >=1)
                {
                    m_view.zoom(1.f / m_scrollAmount);
                    if(m_viewMoveSpeed > 0)
                        m_viewMoveSpeed -= (m_scrollAmount * 2);
                    else
                        m_viewMoveSpeed = 1;
                }
                if(m_event.mouseWheel.delta <= -1)
                {
                    if(m_viewMoveSpeed < 20)
                        m_viewMoveSpeed += (m_scrollAmount * 2);
                    else
                        m_viewMoveSpeed = 20;
                    m_view.zoom(1.5);
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
            m_simDelay += 1000 * Time::deltaTime;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if(m_simDelay > 0)
            m_simDelay -= 1000 * Time::deltaTime;
        else
            m_simDelay = 10;
    }
    
   // move view 
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && m_view.getCenter().x > 0) //&& m_view.getCenter().x - m_view.getSize().x /2.f > 0)
    {
        m_view.move(-m_viewMoveSpeed * Time::deltaTime, 0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && m_view.getCenter().x < m_mapSizeX * m_gridSizeF) //&& m_view.getCenter().x + (m_view.getSize().x/2.f) < (m_mapSizeX * m_gridSizeF))
    {
        m_view.move(m_viewMoveSpeed * Time::deltaTime, 0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && m_view.getCenter().y > 0) //&& m_view.getCenter().y - m_view.getSize().y > 0)
    {
        m_view.move(0.f,-m_viewMoveSpeed * Time::deltaTime);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && m_view.getCenter().y < m_mapSizeY * m_gridSizeF )//&& m_view.getCenter().y + m_view.getSize().y < (m_mapSizeY * m_gridSizeF))
    {
        m_view.move(0.f,m_viewMoveSpeed * Time::deltaTime);
    }

}


void Game::update()
{
    if(m_viewMoveSpeed < 0)
        m_viewMoveSpeed = 1;
    
    if(m_viewMoveSpeed > 20)
        m_viewMoveSpeed = 20;

    pollEvents();
    if(m_window->hasFocus())
        getInput();

    if(m_simDelay < 0){
        m_simDelay = 10;
    }
    
    m_gameOfLife.update(Time::deltaTime,m_simDelay);

}

void Game::renderBoundaries(sf::RenderTarget &target)
{
    target.draw(m_boundaryLeft);
    target.draw(m_boundaryRight);

    target.draw(m_boundaryUp);
    target.draw(m_boundaryDown);
}

void Game::render()
{
    //while(isRunning())
    //{
        m_window->clear();
        m_window->setView(m_view);

        renderBoundaries(*this->m_window);
        m_gameOfLife.render(*this->m_window);

        m_window->setView(m_window->getDefaultView());
        m_gameOfLife.renderUI(*this->m_window);
        m_window->display();

    //}
}

void Game::updateMousePos()
{
    m_mousePosScreen = sf::Mouse::getPosition();
    m_mousePosWindow = sf::Mouse::getPosition(*m_window);
    m_mousePosView = m_window->mapPixelToCoords(m_mousePosWindow);

    if(m_mousePosView.x >= 0.f)
        m_mousePosGrid.x = m_mousePosView.x / static_cast<unsigned>(m_gridSizeF);

    if(m_mousePosView.y >= 0.f)
        m_mousePosGrid.y = m_mousePosView.y / static_cast<unsigned>(m_gridSizeF);

    m_gameOfLife.setMousePosGrid(m_mousePosGrid);

}


void Game::startGLoop()
{
    m_gameOfLife.startSimThread();
    //m_renderThread = std::thread(&Game::render, this);
    while(this->isRunning())
    {
        m_window->setView(m_view);
        Time::initDeltaTime();
        this->updateMousePos();
        m_window->setView(m_window->getDefaultView());
        
        this->update();

        
        this->render();


    }
    m_gameOfLife.joinSimThread();
    //m_renderThread.join();
}
