/**
 * @file engine.h
 * @author Ilya Bardinov (ilya.bardinov@gmail.com)
 * @brief Engine class.
 * @date 2019-02-17
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef _SIMPLE2DENGINE_ENGINE_H_
#define _SIMPLE2DENGINE_ENGINE_H_

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "simple2dengine/configuration.h"
#include "simple2dengine/managers/asset_manager.h"
#include "simple2dengine/managers/input_manager.h"
#include "simple2dengine/managers/loaders/font_loader.h"
#include "simple2dengine/managers/loaders/sound_loader.h"
#include "simple2dengine/managers/loaders/texture_loader.h"
#include "simple2dengine/managers/scene_manager.h"

/**
 * @brief main namespace of simple2dengine.
 *
 */
namespace simple2dengine
{
    /**
     * @brief Engine initialization.
     * It is a starting point for Simple2DEngine.
     * You can init engine with Engine engine(config) and start with engine.run().
     *
     */
    class Engine
    {
      public:
        /**
         * @brief Engine initialization.
         *
         * @param config Configuration for Engine
         * @see Configuration
         */
        Engine(const Configuration& config);
        /**
         * @brief Start Engine.
         * Call it after initialization and activation of scene.
         *
         */
        void run();
        /**
         * @brief Stop Engine.
         * You can call it in any scene. It will stop engine loop.
         *
         */
        void stop();
        /**
         * @brief Get scene manager.
         * @see SceneManager.
         *
         */
        SceneManager& getSceneManager();
        /**
         * @brief Get asset manager.
         * @see AssetManager.
         *
         */
        AssetManager& getAssetManager();
        /**
         * @brief Get input manager.
         * @see InputManager.
         *
         */
        InputManager& getInputManager();
        /**
         * @brief Get current configuration.
         * @see Configuration.
         *
         */
        const Configuration& getConfiguration();
        /**
         * @brief Get render window.
         * It is used by SFML and needed for drawing objects.
         *
         */
        sf::RenderWindow& getRenderWindow();
        /**
         * @brief Set the Background Color of Window.
         *
         * @param color background color of window.
         */
        void setBackgroundColor(const sf::Color& color);

      private:
        /**
         * @brief Update logic of Engine and Nodes.
         *
         * @param deltaInMs - time in milliseconds since last update.
         *
         */
        void update(const int deltaInMs);
        /**
         * @brief Render Nodes.
         *
         */
        void render();

        sf::RenderWindow window;                      // SFML window
        sf::Color backgroundColor = sf::Color::Black; // Window background color
        sf::Clock deltaClock;                         // Help to calculate delta for update method
        bool isRunning = false;                       // Running state
        Configuration configuration;                  // Configuration object (window size, fps, etc)
        // managers
        SceneManager sceneManager; // operates with scenes
        AssetManager assetManager; // operates with assets
        InputManager inputManager; // operates with input
    };
} // namespace simple2dengine

#endif // _SIMPLE2DENGINE_ENGINE_H_
