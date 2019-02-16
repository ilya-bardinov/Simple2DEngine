#ifndef SIMPLE2DENGINE_ENGINE_HPP
#define SIMPLE2DENGINE_ENGINE_HPP

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <string>

namespace Simple2DEngine
{
    /**
     * Initialization class of Engine.
     */
    class Engine
    {
        public:
            /**
             * Default constructor.
             */
            Engine();

            /**
             * Initialize and open an empty window.
             * @param windowWidth window width
             * @param windowheight window height
             * @param windowName window name
             */
            void openWindow(const int windowWidth, const int windowheight, const std::string & windowName);
            void closeWindow();
            bool isWindowOpen() const;

            void startWithNode();

            void update();

            void setFramerateLimit(const unsigned int limit);
        
        private:
            void render();

        private:
            sf::RenderWindow window;
            sf::Clock deltaClock;
            sf::Time frameTimeLimit = sf::Time::Zero;
    };
}
#endif