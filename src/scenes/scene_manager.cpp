#include "simple2dengine/scenes/scene_manager.h"

namespace simple2dengine
{
    SceneManager::SceneManager()
    {

    }

    void SceneManager::pushScene(std::shared_ptr<Node>& node)
    {
        node->setSceneManager(this);
        nodes.push_back(node);
    }

    void SceneManager::popScene()
    {
        nodes.pop_back();
    }
        
    void SceneManager::replaceScene(std::shared_ptr<Node>& node)
    {
        popScene();
        pushScene(node);
    }

    int SceneManager::getScenesCount() const
    {
        return nodes.size();
    }

    void SceneManager::update(int32_t deltaInMs)
    {
        std::shared_ptr<Node> node = nodes.back();
        if(node)
            node->update(deltaInMs);
    }

    void SceneManager::render()
    {
        std::shared_ptr<Node> node = nodes.back();
        if(node)
            node->render();
    }
}