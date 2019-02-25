#include <iostream>

#include "simple2dengine/managers/input_manager.h"

namespace simple2dengine
{
    void InputManager::registerAction(const std::string& actionName, const Keyboard::Key keyboardKey)
    {
        auto it = keyboardActions.find(actionName);
        if (it != keyboardActions.end())
        {
            std::vector<Keyboard::Key> keyVector = it->second;
            for(const auto& key : keyVector)
            {
                if(key == keyboardKey)
                {
                    std::cout << "InputManager::registerAction - action '" << actionName << "' already have key " << keyboardKey << std::endl;
                    return;
                }
            }
        }

        keyboardActions[actionName].push_back(keyboardKey);
    }

    bool InputManager::isActionPressed(const std::string& action)
    {
        auto it = keyboardActions.find(action);
        if (it != keyboardActions.end())
        {
            std::vector<Keyboard::Key> keyVector = it->second;
            for(const auto& key : keyVector)
            {
                if(Keyboard::isKeyPressed(key))
                {
                    return true;
                }
            }
        }
        else
        {
            std::cout << "InputManager::isActionPressed - action '" << action << "' is not registered!" << std::endl;
        }

        return false;
    }
} // simple2dengine
