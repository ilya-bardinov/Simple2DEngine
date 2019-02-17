#include <iostream>

#include "simple2dengine/engine.h"

namespace simple2dengine
{
    Engine::Engine()
    {

    }

    void Engine::openWindow(const int windowWidth, const int windowHeight, const std::string & windowName)
    {
        if(isWindowOpen())
        {
            std::cout << "ERROR: Engine::openWindow: Already opened a window!" << std::endl;
            return;
        }
        // SFML creates window with size parameters and name
        window.create(sf::VideoMode(windowWidth, windowHeight), windowName);
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

    void Engine::startWithScene(std::shared_ptr<Node>& node)
    {
        if(sceneManager)
        {
            std::cout << "ERROR: Engine::startWithScene: Already started with scene!" << std::endl;
            return;
        }
        sceneManager = std::unique_ptr<SceneManager>(new SceneManager());
        sceneManager->pushScene(node);
    }

    void Engine::update()
    {
        // get elapsed time every tick for physics
        // Limit the framerate if needed
        sf::Time deltaTime = deltaClock.restart();
        if (framerateLimit != sf::Time::Zero && framerateLimit - deltaTime > sf::Time::Zero)
        {
            sleep(framerateLimit - deltaTime);
            deltaTime = framerateLimit;
        }

        // it make no sense to render and update if no window
        if (!isWindowOpen())
        {
            return;
        }

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                closeWindow();
        }

        // update scenes in scene manager
        sceneManager->update(deltaTime.asMilliseconds());

        // Now we should display in window all our graphics
        render();
    }

    void Engine::render()
    {
        // clear the window with black color
        window.clear(sf::Color::Black);
        // render scenes in scene manager
        sceneManager->render();
        // end the current frame
        window.display();
    }

    void Engine::setFramerateLimit(const unsigned int limit)
    {
        if (limit > 0)
            framerateLimit = sf::seconds(1.f / limit);
        else
            framerateLimit = sf::Time::Zero;
    }
} // simple2dengine