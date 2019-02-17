#include "simple2dengine/scenes/node.h"

namespace simple2dengine
{
    Node::Node()
    {

    }

    SceneManager* Node::getSceneManager() const
    {
        return sceneManager;
    }

    void Node::setSceneManager(SceneManager* _sceneManager)
    {
        sceneManager = _sceneManager;
    }
}