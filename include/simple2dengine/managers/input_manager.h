/**
 * @file input_manager.h
 * @author Ilya Bardinov (ilya.bardinov@gmail.com)
 * @brief Input Manager
 * @date 2019-02-25
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef _SIMPLE2DENGINE_MANAGERS_INPUT_MANAGER_H_
#define _SIMPLE2DENGINE_MANAGERS_INPUT_MANAGER_H_

#include <string>
#include <vector>
#include <unordered_map>

#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"

#include "simple2dengine/nodes/node.h"

namespace simple2dengine
{
    typedef sf::Keyboard Keyboard;
    typedef sf::Mouse Mouse;
    /**
     * @brief Scene Manager.
     * You can get it from Engine.
     *
     * @see Engine.
     */
    class InputManager
    {
      public:
        /**
         * @brief Attach Action to keyboard button.
         *
         * @param actionName - name of action.
         * @param keyboardKey - keyboard key from SFML.
         */
        void registerAction(const std::string& action, const Keyboard::Key keyboardKey);
        /**
         * @brief Attach Action to mouse button.
         *
         * @param actionName - name of action.
         * @param keyboardKey - mouse button from SFML.
         */
        void registerAction(const std::string& action, const Mouse::Button mouseButton);
        /**
         * @brief Remove Action.
         *
         * @param actionName - name of action.
         */
        void unregisterAction(const std::string& action);
        /**
         * @brief Check if action is pressed or not.
         *
         * @param action - action to check.
         * @return true - if action is pressed.
         * @return false - if action is not pressed.
         */
        bool isActionPressed(const std::string& action) const;
        /**
         * @brief Get the current position of the mouse in window coordinates.
         * This function returns the current position of the mouse cursor, relative to the given window.
         *
         * @param relativeTo - Coordinates from window.
         * @return Current position of the mouse.
         */
        Vector2i getMousePosition(const sf::Window& relativeTo) const;

      private:
        std::unordered_map<std::string, std::vector<Keyboard::Key>> keyboardActions; // actions for keyboard buttons
        std::unordered_map<std::string, std::vector<Mouse::Button>> mouseActions; // actions for mouse buttons
    };

} // simple2dengine

#endif // _SIMPLE2DENGINE_MANAGERS_INPUT_MANAGER_H_
