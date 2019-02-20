/**
 * @file engine.h
 * @author Ilya Bardinov (ilya.bardinov@gmail.com)
 * @brief Starting class.
 * @version 0.1
 * @date 2019-02-17
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef SIMPLE2DENGINE_ENGINE_H_
#define SIMPLE2DENGINE_ENGINE_H_

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <memory>

#include "simple2dengine/configuration.h"
#include "simple2dengine/managers/scene_manager.h"

/**
 * @brief Namespace for Simple2DEngine.
 *
 */
namespace simple2dengine
{
    /**
     * @brief Initialization class of Engine.
     * It is a starting point for Simple2DEngine.
     *
     */
    class Engine
    {
      public:
        /**
         * @brief Construct a new Engine object.
         *
         * @param config Configuration for Engine
         */
        Engine(const Configuration& config);
        /**
         * @brief Start Engine loop.
         *
         */
        void run();
        /**
         * @brief Stop Engine and exit.
         *
         */
        void stop();
        /**
         * @brief Get SceneManager.
         *
         */
        SceneManager& getSceneManager();

      private:
        /**
         * @brief Update logic of Engine and Nodes.
         *
         */
        void update(int delta);
        /**
         * @brief Render Scenes.
         *
         */
        void render();

        // SFML window
        sf::RenderWindow window;
        // time and framerate
        sf::Clock deltaClock;
        // running state
        bool isRunning = false;
        // scene manager
        SceneManager sceneManager;
        // config
        Configuration configuration;
    };
} // simple2dengine

#endif // SIMPLE2DENGINE_ENGINE_H_
