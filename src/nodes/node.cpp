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
        children.push_back(child);
        child->parent = shared_from_this();
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
        this->position = _position;

        for(auto& child : children)
        {
            child->setPosition(child->getPosition());
        }
    }

    void Node::move(const Vector2f& _position)
    {
        setPosition(position + _position);
    }

    const Vector2f& Node::getPosition() const
    {
        return this->position;
    }

    Vector2f Node::getAbsolutePosition() const
    {
        if(parent.expired())
        {
            return this->getPosition();
        }

        auto root = shared_from_this();
        Vector2f ret_position = root->getPosition();

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
            return this->isVisible();
        }

        auto root = shared_from_this();
        bool ret_visible = root->isVisible();

        while (root->getParent() != nullptr && ret_visible)
        {
            root = root->getParent();
            ret_visible = root->isVisible();
        }

        return ret_visible;
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
