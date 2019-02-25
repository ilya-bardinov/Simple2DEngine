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

namespace simple2dengine
{
    typedef sf::Keyboard Keyboard;
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
         * @brief Attach Action to specific keyboard button.
         *
         * @param actionName - name of action.
         * @param keyboardKey - keyboard key from SFML.
         */
        void registerAction(const std::string& actionName, const Keyboard::Key keyboardKey);
        /**
         * @brief Check if action is pressed or not.
         *
         * @param action - action to check.
         * @return true - if action is pressed.
         * @return false - if action is not pressed.
         */
        bool isActionPressed(const std::string& action);

      private:
        std::unordered_map<std::string, std::vector<sf::Keyboard::Key>> keyboardActions; // actions for keyboard buttons
    };

} // simple2dengine

#endif // _SIMPLE2DENGINE_MANAGERS_INPUT_MANAGER_H_
