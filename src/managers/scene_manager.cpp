#include "simple2dengine/managers/scene_manager.h"

namespace simple2dengine
{
    SceneManager::SceneManager() : currentScene(nullptr) { }

    void SceneManager::addScene(const std::string& name, const std::shared_ptr<Node>& scene)
    {
        scenes[name] = scene;
    }

    void SceneManager::removeScene(const std::string& name)
    {
        auto it = scenes.find(name);
        if (it != scenes.end())
        {
            if(currentScene == it->second)
            {
                currentScene->unload();
                scenes.erase(it);
                currentScene = nullptr;
            } else {
                scenes.erase(it);
            }
        }
    }

    void SceneManager::switchToScene(const std::string& name)
    {
        if (currentScene)
        {
            currentScene->unload();
        }

        auto it = scenes.find(name);
        if (it != scenes.end())
        {
            currentScene = it->second;
            if(currentScene)
                currentScene->load();
        }
    }

    int SceneManager::getSceneCount() const
    {
        return scenes.size();
    }

    void SceneManager::clear()
    {
        for (auto scene : scenes)
        {
	        if(scene.second)
                scene.second->unload();
        }
        scenes.clear();
        currentScene = nullptr;
    }

    void SceneManager::update(int deltaInMs)
    {
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
