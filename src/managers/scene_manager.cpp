#include <iostream>

#include "simple2dengine/managers/scene_manager.h"

namespace simple2dengine
{
    void SceneManager::addScene(const std::string& name, std::shared_ptr<Node> scene)
    {
        auto it = scenes.find(name);
        if (it != scenes.end() && it->second)
        {
            std::cout << "SceneManager::addScene - scene '" << name << "' already exist!" << std::endl;
            return;
        }
        scene->notifyCreate();
        scenes[name] = std::move(scene);
    }

    void SceneManager::removeScene(const std::string& name)
    {
        auto it = scenes.find(name);
        if (it != scenes.end() && it->second)
        {
            destroyedScenes.push_back(it->second);
            if(currentScene && currentScene == it->second)
            {
                currentScene->notifyExit();
                currentScene = nullptr;
            }
            it->second->notifyDestroy();
            scenes.erase(it);
        }
        else
        {
            std::cout << "SceneManager::removeScene - scene '" << name << "' doesn't exist!" << std::endl;
        }
    }

    void SceneManager::activateScene(const std::string& name)
    {
        auto it = scenes.find(name);
        if (it != scenes.end())
        {
            if (currentScene)
            {
                currentScene->notifyExit();
            }
            currentScene = it->second;
            if(currentScene)
                currentScene->notifyEnter();
        }
        else
        {
            std::cout << "SceneManager::activateScene - scene '" << name << "' doesn't exist!" << std::endl;
        }
    }

    int SceneManager::getSceneCount() const
    {
        return scenes.size();
    }

    void SceneManager::clear()
    {
        if (currentScene)
        {
            currentScene->notifyExit();
        }

        for (auto& scene : scenes)
        {
	        if(scene.second)
                scene.second->notifyDestroy();
        }
    }

    void SceneManager::update(unsigned int deltaInMs)
    {
        if(destroyedScenes.size() > 0)
        {
            destroyedScenes.clear();
        }

        if (currentScene)
        {
            currentScene->update(deltaInMs);
        }
    }

    void SceneManager::render()
    {
        if (currentScene)
        {
            currentScene->render();
        }
    }
}
