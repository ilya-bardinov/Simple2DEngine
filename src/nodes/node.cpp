#include <algorithm>
#include <iostream>

#include "simple2dengine/engine.h"
#include "simple2dengine/nodes/node.h"

namespace simple2dengine
{
    bool Node::addChild(std::shared_ptr<Node> child)
    {
        if(!child)
        {
            return false;
        }

        if(!child->parent.expired())
        {
            std::cout << "Node::addChild - child '" << child->getName() << "' already has a parent!"
                      << std::endl;
            return false;
        }

        child->engine = this->engine;
        child->parent = shared_from_this();
        child->index = children.size();
        children.push_back(child);

        child->onAddedToTree();

        child->notifyCreate();

        if(state == NodeState::Updating && child->state == NodeState::None)
        {
            child->notifyEnter();
        }

        return true;
    }

    bool Node::removeChild(const std::string& childName)
    {
        const auto it =
            std::find_if(children.begin(), children.end(), [&](const std::shared_ptr<Node>& child) {
                return child->getName() == childName;
            });

        if(it != children.end())
        {
            (*it)->parent = std::shared_ptr<Node>(nullptr);
            (*it)->notifyDestroy();
            children.erase(it);
        }
        else
        {
            std::cout << "Node::removeChild - child '" << childName << "' not found in node tree!"
                      << std::endl;
            return false;
        }

        return true;
    }

    void Node::clear()
    {
        for(const auto& child : children)
        {
            child->parent = std::shared_ptr<Node>(nullptr);
            child->notifyDestroy();
        }
        children.clear();
    }

    int Node::getIndex() const
    {
        return index;
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
        auto root = shared_from_this();
        while(root->getParent() != nullptr)
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
        if(path.empty())
        {
            return shared_from_this();
        }
        else if(path[0] == '/')
        {
            return getRoot()->getNode(path.substr(1));
        }
        else
        {
            const size_t pos = path.find("/");
            const std::string childpath = path.substr(0, pos);

            if(childpath == ".")
            {
                if(pos == std::string::npos)
                {
                    return shared_from_this();
                }
                else
                {
                    return getNode(path.substr(pos + 1));
                }
            }
            else if(childpath == "..")
            {
                if(pos == std::string::npos)
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

                for(auto& _child : children)
                {
                    if(_child->getName() == childpath)
                    {
                        child = _child;
                        break;
                    }
                }

                if(pos == std::string::npos)
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

    void Node::notifyInput(sf::Event event)
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
            if(child->state < NodeState::Creating)
            {
                child->notifyCreate();
            }
        }
    }

    void Node::notifyEnter()
    {
        state = NodeState::Entering;
        onEnter();

        for(auto& child : children)
        {
            if(child->state < NodeState::Entering)
            {
                child->notifyEnter();
            }
        }

        state = NodeState::Updating;
    }

    void Node::notifyExit()
    {
        state = NodeState::Exiting;

        for(auto& child : children)
        {
            if(child->state == NodeState::None)
            {
                child->notifyCreate();
                child->notifyEnter();
            }

            child->notifyExit();
        }

        onExit();
    }

    void Node::notifyDestroy()
    {
        state = NodeState::Destroying;

        for(auto& child : children)
        {
            if(child->state == NodeState::None)
            {
                child->notifyCreate();
            }

            child->notifyDestroy();
        }

        onDestroy();

        state = NodeState::None;
    }
} // namespace simple2dengine
