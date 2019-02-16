#include "Simple2DEngine/Engine.hpp"

namespace Simple2DEngine
{
    Engine::Engine()
    {

    }

    void Engine::openWindow(const int windowWidth, const int windowheight, const std::string & windowName)
    {
        // SFML creates window with size parameters and name
        window.create(sf::VideoMode(windowWidth, windowheight), windowName);
    }

    void Engine::closeWindow()
    {
        if(isWindowOpen())
            window.close();
    }

    bool Engine::isWindowOpen() const
    {
        return window.isOpen();
    }

    void Engine::startWithNode()
    {
        
    }

    void Engine::update()
    {
        // get elapsed time every tick for physics
        // Limit the framerate if needed
        sf::Time deltaTime = deltaClock.restart();
        if (frameTimeLimit != sf::Time::Zero && frameTimeLimit - deltaTime > sf::Time::Zero)
        {
            sleep(frameTimeLimit - deltaTime);
        }

        if (isWindowOpen())
        {
            // check all the window's events that were triggered since the last iteration of the loop
            sf::Event event;
            while (window.pollEvent(event))
            {
                // "close requested" event: we close the window
                if (event.type == sf::Event::Closed)
                    closeWindow();
            }
        }

        // Now we should display in window all our graphics
        render();
    }

    void Engine::render()
    {
        // clear the window with black color
        window.clear(sf::Color::Black);
        // end the current frame
        window.display();
    }

    void Engine::setFramerateLimit(const unsigned int limit)
    {
        if (limit > 0)
            frameTimeLimit = sf::seconds(1.f / limit);
        else
            frameTimeLimit = sf::Time::Zero;
    }
}