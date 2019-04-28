#include <iostream>

#include "simple2dengine/managers/scene_manager.h"

namespace simple2dengine
{
    void SceneManager::addScene(std::shared_ptr<Node> scene)
    {
        const std::string name = scene->getName();
        const auto it = scenes.find(name);
        if(it != scenes.end() && it->second)
        {
            std::cout << "SceneManager::addScene - scene '" << name << "' already exist in scene tree!"
                      << std::endl;
            return;
        }
        scene->engine = this->engine;

        scenes[name] = std::move(scene);
        scenes[name]->notifyCreate();
    }

    void SceneManager::removeSceneImmediately(std::shared_ptr<Node> scene)
    {
        const std::string name = scene->getName();
        if(currentScene == scene)
        {
            currentScene->notifyExit();
            currentScene = nullptr;
        }
        scene->notifyDestroy();
        scenes.erase(name);
    }

    void SceneManager::removeScene(std::shared_ptr<Node> scene)
    {
        const std::string name = scene->getName();
        removedScenes.push_back(scene);
        if(currentScene == scene)
        {
            currentScene->notifyExit();
            currentScene = nullptr;
        }
        scene->notifyDestroy();
        scenes.erase(name);
    }

    void SceneManager::activateScene(std::shared_ptr<Node> scene)
    {
        const std::string name = scene->getName();
        if(currentScene)
        {
            currentScene->notifyExit();
        }
        currentScene = scene;
        currentScene->notifyEnter();
    }

    int SceneManager::getScenesCount() const
    {
        return scenes.size();
    }

    std::shared_ptr<Node> SceneManager::getScene(const std::string& name)
    {
        const auto it = scenes.find(name);
        if(it != scenes.end())
        {
            return it->second;
        }
        else
        {
            std::cout << "SceneManager::getScene - scene '" << name << "' doesn't exist!" << std::endl;
        }

        return nullptr;
    }

    void SceneManager::clear()
    {
        if(currentScene)
        {
            currentScene->notifyExit();
        }
        currentScene = nullptr;

        for(auto& scene : scenes)
        {
            if(scene.second)
            {
                scene.second->notifyDestroy();
            }
        }
        scenes.clear();
    }

    void SceneManager::update(const int deltaInMs)
    {
        if(removedScenes.size() > 0)
        {
            removedScenes.clear();
        }

        if(currentScene)
        {
            currentScene->update(deltaInMs);
        }
    }

    void SceneManager::render()
    {
        if(currentScene)
        {
            currentScene->render();
        }
    }

    void SceneManager::input(const sf::Event& event)
    {
        if(currentScene)
        {
            currentScene->notifyInput(event);
        }
    }
} // namespace simple2dengine
