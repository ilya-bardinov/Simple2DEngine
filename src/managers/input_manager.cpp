#include <iostream>

#include "simple2dengine/managers/input_manager.h"

namespace simple2dengine
{
    void InputManager::registerAction(const std::string& action, const Keyboard::Key keyboardKey)
    {
        auto it = keyboardActions.find(action);
        if (it != keyboardActions.end())
        {
            std::vector<Keyboard::Key> keyVector = it->second;
            for(const auto& key : keyVector)
            {
                if(key == keyboardKey)
                {
                    std::cout << "InputManager::registerAction - action '" << action << "' already have key " << keyboardKey << std::endl;
                    return;
                }
            }
        }

        keyboardActions[action].push_back(keyboardKey);
    }

    void InputManager::registerAction(const std::string& action, const Mouse::Button mouseButton)
    {
        auto it = mouseActions.find(action);
        if (it != mouseActions.end())
        {
            std::vector<Mouse::Button> button = it->second;
            for(const auto& key : button)
            {
                if(key == mouseButton)
                {
                    std::cout << "InputManager::registerAction - action '" << action << "' already have mouse button " << mouseButton << std::endl;
                    return;
                }
            }
        }

        mouseActions[action].push_back(mouseButton);
    }

    void InputManager::unregisterAction(const std::string& action)
    {
        auto keyboardIt = keyboardActions.find(action);
        if (keyboardIt != keyboardActions.end())
        {
            keyboardActions.erase(keyboardIt);
        }

        auto mouseIt = mouseActions.find(action);
        if (mouseIt != mouseActions.end())
        {
            mouseActions.erase(mouseIt);
        }
    }

    bool InputManager::isActionPressed(const std::string& action) const
    {
        // check keyboard buttons
        auto itKeyboard = keyboardActions.find(action);
        if (itKeyboard != keyboardActions.end())
        {
            std::vector<Keyboard::Key> keyVector = itKeyboard->second;
            for(const auto& key : keyVector)
            {
                if(Keyboard::isKeyPressed(key))
                {
                    return true;
                }
            }
        }
        // check mouse buttons
        auto itMouse = mouseActions.find(action);
        if (itMouse != mouseActions.end())
        {
            std::vector<Mouse::Button> button = itMouse->second;
            for(const auto& key : button)
            {
                if(Mouse::isButtonPressed(key))
                {
                    return true;
                }
            }
        }

        return false;
    }

    Vector2i InputManager::getMousePosition(const sf::Window& relativeTo) const
    {
        return Mouse::getPosition(relativeTo);
    }
} // simple2dengine
