#include <iostream>

#include "simple2dengine/managers/input_manager.h"

namespace simple2dengine
{
    void InputManager::registerAction(const std::string& action, const sf::Keyboard::Key keyboardKey)
    {
        const auto it = keyboardActions.find(action);
        if (it != keyboardActions.end())
        {
            const std::vector<sf::Keyboard::Key> keyVector = it->second;
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

    void InputManager::registerAction(const std::string& action, const sf::Mouse::Button mouseButton)
    {
        const auto it = mouseActions.find(action);
        if (it != mouseActions.end())
        {
            const std::vector<sf::Mouse::Button> button = it->second;
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
        const auto keyboardIt = keyboardActions.find(action);
        if (keyboardIt != keyboardActions.end())
        {
            keyboardActions.erase(keyboardIt);
        }

        const auto mouseIt = mouseActions.find(action);
        if (mouseIt != mouseActions.end())
        {
            mouseActions.erase(mouseIt);
        }
    }

    bool InputManager::isActionPressed(const std::string& action) const
    {
        // check keyboard buttons
        const auto itKeyboard = keyboardActions.find(action);
        if (itKeyboard != keyboardActions.end())
        {
            const std::vector<sf::Keyboard::Key> keyVector = itKeyboard->second;
            for(const auto& key : keyVector)
            {
                if(sf::Keyboard::isKeyPressed(key))
                {
                    return true;
                }
            }
        }
        // check mouse buttons
        const auto itMouse = mouseActions.find(action);
        if (itMouse != mouseActions.end())
        {
            const std::vector<sf::Mouse::Button> button = itMouse->second;
            for(const auto& key : button)
            {
                if(sf::Mouse::isButtonPressed(key))
                {
                    return true;
                }
            }
        }

        return false;
    }

    sf::Vector2i InputManager::getMousePosition(const sf::Window& relativeTo) const
    {
        return sf::Mouse::getPosition(relativeTo);
    }
} // simple2dengine
