#include <iostream>

#include "simple2dengine/engine.h"

namespace simple2dengine
{
    Engine::Engine(const Configuration& config) : sceneManager(*this), configuration(config)
    {
        window.create(sf::VideoMode(configuration.window.width, configuration.window.height), configuration.window.name);
    }

    void Engine::run()
    {
        isRunning = true;

        while (isRunning)
        {
            sf::Time deltaTime = deltaClock.restart();

            update(deltaTime.asMilliseconds());

            // Limit the framerate if needed
            if (configuration.fps > 0)
            {
                sf::Time currFramerate = sf::seconds(static_cast<float>(1.0f / configuration.fps));
                if(currFramerate > deltaTime)
                    sf::sleep(currFramerate - deltaTime);
            }
        }
    }

    void Engine::stop()
    {
        isRunning = false;
    }

    SceneManager& Engine::getSceneManager()
    {
        return sceneManager;
    }

    void Engine::update(int delta)
    {

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
            {
                stop();
                window.close();
            }
        }

        // update scenes in scene manager
        sceneManager.update(delta);

        // Now we should display in window all our graphics
        render();
    }

    void Engine::render()
    {
        // clear the window with black color
        window.clear(sf::Color::Black);
        // render scenes in scene manager
        sceneManager.render();
        // end the current frame
        window.display();
    }
} // simple2dengine
