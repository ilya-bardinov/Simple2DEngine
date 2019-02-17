#include "simple2dengine/scenes/node.h"

namespace simple2dengine
{
    Node::Node()
    {

    }

    void Node::update(int32_t deltaInMs)
    {

    }

    void Node::render()
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