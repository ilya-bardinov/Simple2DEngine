#include "simple2dengine/managers/scene_manager.h"

namespace simple2dengine
{
    SceneManager::SceneManager(Engine& engine) : engine(engine), currentScene(nullptr) { }

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
        if (currentScene != nullptr)
        {
            currentScene->unload();
        }

        auto it = scenes.find(name);
        if (it != scenes.end())
        {
            currentScene = it->second;
            if(currentScene != nullptr)
                currentScene->load();
        }
    }

    int SceneManager::getSceneCount() const
    {
        return scenes.size();
    }

    void SceneManager::update(int deltaInMs)
    {
        if (currentScene != nullptr)
        {
            currentScene->update(deltaInMs);
        }
    }

    void SceneManager::render()
    {
        if (currentScene != nullptr)
        {
            currentScene->render();
        }
    }
}
