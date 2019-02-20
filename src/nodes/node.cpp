#include "simple2dengine/nodes/node.h"

namespace simple2dengine
{
    Node::Node(Engine& engine) : engine(engine) { }

    Node::~Node() { }

    void Node::load() { }

    void Node::unload() { }

    void Node::addChild(const std::shared_ptr<Node>& child)
    {
        children.push_back(child);
    }

    void Node::removeChild(const std::shared_ptr<Node>& child)
    {
        for (auto it = children.begin(); it != children.end(); it++)
        {
            if (*it == child)
            {
                children.erase(it);
                break;
            }
        }
    }

    void Node::update(int32_t deltaInMs)
    {
        for(const auto& child : children)
        {
            child->update(deltaInMs);
        }
    }

    void Node::render()
    {
        for(const auto& child : children)
        {
            child->render();
        }
    }
}
