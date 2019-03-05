#include <algorithm>
#include <iostream>

#include "simple2dengine/nodes/node.h"
#include "simple2dengine/engine.h"

namespace simple2dengine
{
    void Node::addChild(std::shared_ptr<Node> child)
    {
        if(!child->parent.expired())
        {
            std::cout << "Node::addChild - child '" << child->getName() << "' already has a parent!" << std::endl;
            return;
        }
        child->parent = shared_from_this();
        children.push_back(std::move(child));
    }

    void Node::removeChild(std::shared_ptr<Node> child)
    {
        auto it = std::find(children.begin(), children.end(), child);
        if (it != children.end())
        {
            child->parent = std::shared_ptr<Node>(nullptr);
            child->notifyDestroy();
            children.erase(it);
        }
        else
        {
            std::cout << "Node::removeChild - child '" << child->getName() << "' not found in node tree!" << std::endl;
        }
    }

    const std::string& Node::getName() const
    {
        return name;
    }

    std::shared_ptr<Node> Node::getParent() const
    {
        return parent.lock();
    }

    std::shared_ptr<Node> Node::getRoot()
    {
        if(parent.expired())
        {
            return nullptr;
        }

        auto root = shared_from_this();
        while (root->getParent() != nullptr)
        {
            root = root->getParent();
        }

        return root;
    }

    const std::vector<std::shared_ptr<Node>>& Node::getChildren() const
    {
        return children;
    }

    std::shared_ptr<Node> Node::getNode(const std::string& path)
    {
        // taken from https://github.com/linkdd/sdl-game-engine/blob/master/src/node.cpp
        if (path.empty())
        {
            return shared_from_this();
        }
        else if (path[0] == '/')
        {
            return getRoot()->getNode(path.substr(1));
        }
        else
        {
            size_t pos = path.find("/");
            std::string childpath = path.substr(0, pos);

            if (childpath == ".")
            {
                if (pos == std::string::npos)
                {
                    return shared_from_this();
                }
                else
                {
                    return getNode(path.substr(pos + 1));
                }
            }
            else if (childpath == "..")
            {
                if (pos == std::string::npos)
                {
                    return getParent();
                }
                else
                {
                    return getParent()->getNode(path.substr(pos + 1));
                }
            }
            else
            {
                std::shared_ptr<Node> child = nullptr;

                for (auto& _child : children)
                {
                    if (_child->getName() == childpath)
                    {
                        child = _child;
                        break;
                    }
                }

                if (pos == std::string::npos)
                {
                    return child;
                }
                else
                {
                    return child->getNode(path.substr(pos + 1));
                }
            }
        }

        return nullptr;
    }

    void Node::update(int deltaInMs)
    {
        onUpdate(deltaInMs);

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

    void Node::notifyInput(Event event)
    {
        onInput(event);

        for(auto& child : children)
        {
            child->notifyInput(event);
        }
    }

    void Node::notifyCreate()
    {
        state = NodeState::Creating;
        onCreate();

        for(auto& child : children)
        {
            child->notifyCreate();
        }
    }

    void Node::notifyEnter()
    {
        state = NodeState::Entering;
        onEnter();

        for(auto& child : children)
        {
            child->notifyEnter();
        }

        state = NodeState::Updating;
    }

    void Node::notifyExit()
    {
        state = NodeState::Exiting;

        for(auto& child : children)
        {
            child->notifyExit();
        }

        onExit();
    }

    void Node::notifyDestroy()
    {
        state = NodeState::Destroying;

        for(auto& child : children)
        {
            child->notifyDestroy();
        }

        onDestroy();

        state = NodeState::None;
    }
}
