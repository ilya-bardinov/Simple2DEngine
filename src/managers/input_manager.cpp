#include <iostream>

#include "simple2dengine/managers/input_manager.h"

namespace simple2dengine
{
    void InputManager::registerAction(const std::string& action, const sf::Keyboard::Key keyboardButton)
    {
        const auto it = keyboardActions.find(action);
        if(it != keyboardActions.end())
        {
            const std::vector<sf::Keyboard::Key> vector = it->second;
            for(const sf::Keyboard::Key& key : vector)
            {
                if(key == keyboardButton)
                {
                    std::cout << "InputManager::registerAction - action '" << action
                              << "' already have keyboard button " << keyboardButton << std::endl;
                    return;
                }
            }
        }

        keyboardActions[action].push_back(keyboardButton);
    }

    void InputManager::registerAction(const std::string& action, const sf::Mouse::Button mouseButton)
    {
        const auto it = mouseActions.find(action);
        if(it != mouseActions.end())
        {
            const std::vector<sf::Mouse::Button> vector = it->second;
            for(const sf::Mouse::Button& button : vector)
            {
                if(button == mouseButton)
                {
                    std::cout << "InputManager::registerAction - action '" << action
                              << "' already have mouse button " << mouseButton << std::endl;
                    return;
                }
            }
        }

        mouseActions[action].push_back(mouseButton);
    }

    void InputManager::unregisterAction(const std::string& action)
    {
        const auto keyboardIt = keyboardActions.find(action);
        if(keyboardIt != keyboardActions.end())
        {
            keyboardActions.erase(keyboardIt);
        }

        const auto mouseIt = mouseActions.find(action);
        if(mouseIt != mouseActions.end())
        {
            mouseActions.erase(mouseIt);
        }
    }

    bool InputManager::isActionPressed(const std::string& action) const
    {
        // check keyboard buttons
        const auto keyboardIt = keyboardActions.find(action);
        if(keyboardIt != keyboardActions.end())
        {
            const std::vector<sf::Keyboard::Key> vector = keyboardIt->second;
            for(const sf::Keyboard::Key& key : vector)
            {
                if(sf::Keyboard::isKeyPressed(key))
                {
                    return true;
                }
            }
        }
        // check mouse buttons
        const auto mouseIt = mouseActions.find(action);
        if(mouseIt != mouseActions.end())
        {
            const std::vector<sf::Mouse::Button> vector = mouseIt->second;
            for(const sf::Mouse::Button& button : vector)
            {
                if(sf::Mouse::isButtonPressed(button))
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
} // namespace simple2dengine
