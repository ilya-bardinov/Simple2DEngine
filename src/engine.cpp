#include <iostream>

#include "simple2dengine/engine.h"

namespace simple2dengine
{
    Engine::Engine(const Configuration& config) : configuration(config)
    {
        textureLoader = std::make_shared<TextureLoader>();
        soundLoader = std::make_shared<SoundLoader>();
        assetManager.registerLoader(textureLoader, { "png", "jpg" } );
        assetManager.registerLoader(soundLoader, { "wav", "ogg" } );

        window.create(sf::VideoMode(configuration.window.width, configuration.window.height), configuration.window.name);

        if (configuration.fps > 0)
        {
            window.setFramerateLimit(configuration.fps);
        }
    }

    void Engine::run()
    {
        isRunning = true;
        while (isRunning)
        {
            sf::Time deltaTime = deltaClock.restart();

            update(deltaTime.asMilliseconds());
        }
    }

    void Engine::stop()
    {
        isRunning = false;
        sceneManager.clear();
    }

    SceneManager& Engine::getSceneManager()
    {
        return sceneManager;
    }

    AssetManager& Engine::getAssetManager()
    {
        return assetManager;
    }

    sf::RenderWindow& Engine::getRenderWindow()
    {
        return window;
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
