#include <algorithm>
#include <iostream>

#include "simple2dengine/nodes/node.h"

namespace simple2dengine
{
    void Node::addChild(const std::shared_ptr<Node>& child)
    {
        if(!child->parent.expired())
        {
            std::cout << "Node::addChild - child already has a parent!" << std::endl;
            return;
        }
        children.push_back(child);
        child->parent = shared_from_this();
    }

    void Node::removeChild(const std::shared_ptr<Node>& child)
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
            std::cout << "Node::removeChild - child not found in node!" << std::endl;
        }
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

    void Node::setPosition(const sf::Vector2f &_position)
    {
        this->position = _position;
    }

    void Node::move(const sf::Vector2f &_position)
    {
        setPosition(position + _position);
    }

    const sf::Vector2f& Node::getPosition() const
    {
        return this->position;
    }

    sf::Vector2f Node::getAbsolutePosition() const
    {
        if(parent.expired())
        {
            return this->getPosition();
        }

        auto root = shared_from_this();
        sf::Vector2f ret_position = root->getPosition();

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
