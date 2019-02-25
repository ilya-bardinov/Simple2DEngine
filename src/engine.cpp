#include <iostream>

#include "simple2dengine/engine.h"

namespace simple2dengine
{
    Engine::Engine(const Configuration& config) : configuration(config)
    {
        // we want to support different type of assets so registering loaders and file extensions
        assetManager.registerLoader(std::make_shared<TextureLoader>(), { "png", "jpg" } );
        assetManager.registerLoader(std::make_shared<SoundLoader>(), { "wav", "ogg" } );
        assetManager.registerLoader(std::make_shared<FontLoader>(), { "ttf" } );
        // window creating
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
            // we need delta for update
            sf::Time deltaTime = deltaClock.restart();
            update(deltaTime.asMilliseconds());
        }
    }

    void Engine::stop()
    {
        isRunning = false;
        // when we decide to stop an engine we need nodes to exit from current scene
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
