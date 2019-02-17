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

#include "simple2dengine/scenes/node.h"
#include "simple2dengine/scenes/scene_manager.h"

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
         * @brief Default constructor.
         * 
         */
        Engine();
        /**
         * @brief Initialize and open an empty window of specified size and name.
         * 
         * @param windowWidth window width
         * @param windowHeight window height
         * @param windowName window name
         */
        void openWindow(const int windowWidth, const int windowHeight, const std::string& windowName);
        /**
         * @brief Close window.
         * 
         */
        void closeWindow();
        /**
         * @brief Check if window is open or not.
         * 
         * @return true if window is open. 
         * @return false if window is not open.
         */
        bool isWindowOpen() const;
        /**
         * @brief Add Scene to Engine to display it.
         * 
         * @param node initial scene
         */
        void startWithScene(std::shared_ptr<Node>& node);
        /**
         * @brief Update logic of Engine and Scene.
         * 
         */
        void update();
        /**
         * @brief Set the Framerate Limit in window.
         * 
         * @param limit framerate limit 
         */
        void setFramerateLimit(const unsigned int limit);

      private:
        /**
         * @brief Render Scenes.
         * 
         */
        void render();

        // SFML window
        sf::RenderWindow window;
        // time and framerate
        sf::Clock deltaClock;
        sf::Time framerateLimit = sf::Time::Zero;
        // scene manager
        std::unique_ptr<SceneManager> sceneManager;
    };
} // simple2dengine

#endif // SIMPLE2DENGINE_ENGINE_H_