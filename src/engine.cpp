#include <iostream>

#include "simple2dengine/engine.h"

namespace simple2dengine
{
    Engine::Engine(const Configuration& config) : configuration(config)
    {
        // we want to support different type of assets so registering loaders and file extensions
        assetManager.registerLoader(std::make_shared<TextureLoader>(),
                                    {"png", "jpg", "bmp", "dds", "tga", "psd", "gif"});
        assetManager.registerLoader(std::make_shared<SoundLoader>(), {"wav", "ogg"});
        assetManager.registerLoader(std::make_shared<FontLoader>(), {"ttf"});
        // window creating
        window.create(sf::VideoMode(configuration.window.width, configuration.window.height,
                                    configuration.window.bitsPerPixel),
                      configuration.window.name, configuration.window.style);
        window.setPosition(configuration.window.position);
        window.setVerticalSyncEnabled(configuration.framerate.verticalSync);
        if(configuration.framerate.fps > 0)
        {
            window.setFramerateLimit(configuration.framerate.fps);
        }

        sceneManager.engine = this;
    }

    void Engine::run()
    {
        isRunning = true;
        while(isRunning)
        {
            // we need delta for update
            sf::Time deltaTime = deltaClock.restart();
            // Let's make some game and engine logic
            update(deltaTime.asMilliseconds());
            // Now we have to display in the window all our pixels
            render();
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

    InputManager& Engine::getInputManager()
    {
        return inputManager;
    }

    const Configuration& Engine::getConfiguration()
    {
        return configuration;
    }

    sf::RenderWindow& Engine::getRenderWindow()
    {
        return window;
    }

    void Engine::setBackgroundColor(const sf::Color& color)
    {
        backgroundColor = color;
    }

    void Engine::update(int delta)
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while(window.pollEvent(event))
        {
            // "close requested" event: we close the window
            switch(event.type)
            {
                case sf::Event::Closed:
                    stop();
                    window.close();
                    break;
                case sf::Event::Resized:
                {
                    // windowView.setSize(event.size.width, event.size.height);
                    sf::FloatRect visibleArea(0.f, 0.f, static_cast<float>(event.size.width),
                                              static_cast<float>(event.size.height));
                    window.setView(sf::View(visibleArea));
                }
                break;
                case sf::Event::TextEntered:
                case sf::Event::KeyPressed:
                case sf::Event::KeyReleased:
                case sf::Event::MouseWheelScrolled:
                case sf::Event::MouseButtonPressed:
                case sf::Event::MouseButtonReleased:
                case sf::Event::MouseMoved:
                {
                    sceneManager.input(event);
                }
                break;
                default:
                    break;
            }
        }
        // update scenes in scene manager
        sceneManager.update(delta);
    }

    void Engine::render()
    {
        // clear the window with background color
        window.clear(backgroundColor);
        // render scenes in scene manager
        sceneManager.render();
        // end the current frame
        window.display();
    }
} // namespace simple2dengine
