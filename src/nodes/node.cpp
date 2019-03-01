#include <algorithm>
#include <iostream>

#include "simple2dengine/nodes/node.h"

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
        updateState(child);
        children.push_back(std::move(child));
    }

    void Node::removeChild(std::shared_ptr<Node> child)
    {
        auto it = std::find(children.begin(), children.end(), child);
        if (it != children.end())
        {
            child->parent = std::shared_ptr<Node>(nullptr);
            if(state != NodeState::Destroying)
            {
                child->notifyExit();
            }
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

    void Node::setPosition(const Vector2f& _position)
    {
        position = _position;

        updatePosition();
    }

    void Node::move(const Vector2f& _position)
    {
        setPosition(position + _position);
    }

    const Vector2f& Node::getPosition() const
    {
        return position;
    }

    Vector2f Node::getAbsolutePosition() const
    {
        if(parent.expired())
        {
            return getPosition();
        }

        auto root = shared_from_this();
        Vector2f ret_position = root->getPosition();
        // now we need to get absolute position by summing position of all parents
        while (root->getParent() != nullptr)
        {
            root = root->getParent();
            ret_position += root->getPosition();
        }

        return ret_position;
    }

    void Node::setVisible(bool isVisible)
    {
        this->visible = isVisible;
    }

    bool Node::isVisible() const
    {
        return visible;
    }

    bool Node::isAbsoluteVisible() const
    {
        if(parent.expired())
        {
            return isVisible();
        }

        auto root = shared_from_this();
        bool ret_visible = root->isVisible();
        // now we need to get absolute visibility checking all parents
        // if we find that parent is invisible we should stop and return false
        while (root->getParent() != nullptr && ret_visible)
        {
            root = root->getParent();
            ret_visible = root->isVisible();
        }

        return ret_visible;
    }

    void Node::setAnchor(const Anchor nodeAnchor)
    {
        anchor = nodeAnchor;

        updatePosition();
    }

    Anchor Node::getAnchor()
    {
        return anchor;
    }

    Vector2f Node::getSize() const
    {
        return Vector2f(0.0f, 0.0f);
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
        onExit();

        for(auto& child : children)
        {
            child->notifyExit();
        }
    }

    void Node::notifyDestroy()
    {
        state = NodeState::Destroying;
        onDestroy();

        for(auto& child : children)
        {
            child->notifyDestroy();
        }
    }

    void Node::updatePosition()
    {
        // we need all children update their position
        for(auto& child : children)
        {
            child->updatePosition();
        }
    }

    void Node::updateState(std::shared_ptr<Node> child)
    {
        switch(state)
        {
            case NodeState::Entering:
                child->notifyCreate();
                break;
            case NodeState::Updating:
            case NodeState::Exiting:
                child->notifyCreate();
                child->notifyEnter();
                break;
            case NodeState::Destroying: // is there any reason to call create and enter
                child->notifyCreate();  // if we wanna exit and destroy?
                child->notifyEnter();
                child->notifyExit();
            default:
                break;
        }
    }
}
