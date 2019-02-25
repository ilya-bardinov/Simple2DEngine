/**
 * @file engine.h
 * @author Ilya Bardinov (ilya.bardinov@gmail.com)
 * @brief Engine main class.
 * @date 2019-02-17
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef _SIMPLE2DENGINE_ENGINE_H_
#define _SIMPLE2DENGINE_ENGINE_H_

#include <string>
#include <memory>

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "simple2dengine/configuration.h"
#include "simple2dengine/managers/scene_manager.h"
#include "simple2dengine/managers/asset_manager.h"
#include "simple2dengine/managers/loaders/texture_loader.h"
#include "simple2dengine/managers/loaders/sound_loader.h"
#include "simple2dengine/managers/loaders/font_loader.h"

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
         * @brief Get render window.
         * It is used by SFML and needed for drawing objects.
         *
         */
        sf::RenderWindow& getRenderWindow();

      private:
        /**
         * @brief Update logic of Engine and Nodes.
         *
         */
        void update(int deltaInMs);
        /**
         * @brief Render Nodes.
         *
         */
        void render();

        sf::RenderWindow window;        // SFML window
        sf::Clock deltaClock;           // Help to calculate delta for update method
        bool isRunning = false;         // Running state
        Configuration configuration;    // Configuration object (window size, fps, etc)
        // managers
        SceneManager sceneManager;      // used by getSceneManager() method
        AssetManager assetManager;      // used by getAssetManager() method
    };
} // simple2dengine

#endif // _SIMPLE2DENGINE_ENGINE_H_
