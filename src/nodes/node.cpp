#include "simple2dengine/nodes/node.h"

namespace simple2dengine
{
    void Node::addChild(const std::shared_ptr<Node>& child)
    {
        children.push_back(child);
    }

    void Node::removeChild(const std::shared_ptr<Node>& child)
    {
        auto it = find(children.begin(), children.end(), child);
        if (it != children.end())
        {
            child->notifyDestroy();
            children.erase(it);
        }
    }

    void Node::update(int deltaInMs)
    {
        this->onUpdate(deltaInMs);

        for(auto& child : children)
        {
            child->update(deltaInMs);
        }
    }

    void Node::render()
    {
        for(auto& child : children)
        {
            child->render();
        }
    }

    void Node::notifyCreate()
    {
        this->onCreate();

        for(auto& child : children)
        {
            child->notifyCreate();
        }
    }

    void Node::notifyEnter()
    {
        this->onEnter();

        for(auto& child : children)
        {
            child->notifyEnter();
        }
    }

    void Node::notifyExit()
    {
        this->onExit();

        for(auto& child : children)
        {
            child->notifyExit();
        }
    }

    void Node::notifyDestroy()
    {
        this->onDestroy();

        for(auto& child : children)
        {
            child->notifyDestroy();
        }
    }
}
