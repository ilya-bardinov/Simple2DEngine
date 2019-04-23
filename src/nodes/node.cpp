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
        children.push_back(child);

        if(state == NodeState::Updating)
        {
            child->notifyEnter();
        }

        return true;
    }

    bool Node::removeChild(std::shared_ptr<Node> child)
    {
        const auto it = std::find(children.begin(), children.end(), child);

        if(it != children.end())
        {
            if(state == NodeState::Updating)
            {
                (*it)->notifyExit();
            }
            (*it)->notifyDestroy();
            (*it)->parent = std::shared_ptr<Node>(nullptr);
            children.erase(it);
        }
        else
        {
            std::cout << "Node::removeChild - child '" << child->getName()
                      << "' not found in node tree!" << std::endl;
            return false;
        }

        return true;
    }

    std::shared_ptr<Node> Node::getChild(unsigned int index)
    {
        if(index < children.size())
        {
            return children[index];
        }

        return nullptr;
    }

    std::shared_ptr<Node> Node::getChild(const std::string& childName)
    {
        const auto it =
            std::find_if(children.begin(), children.end(), [&](const std::shared_ptr<Node>& child) {
                return child->getName() == childName;
            });

        if(it != children.end())
        {
            return (*it);
        }

        return nullptr;
    }

    unsigned int Node::getIndex() const
    {
        std::shared_ptr<Node> parentNode = getParent();
        if(parentNode != nullptr)
        {
            const auto it = std::find(parentNode->getChildren().begin(),
                                      parentNode->getChildren().end(), shared_from_this());
            if(it != parentNode->getChildren().end())
            {
                return std::distance(parentNode->getChildren().begin(), it);
            }
        }

        return 0;
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

    void Node::swap(unsigned int firstIndex, unsigned int secondIndex)
    {
        if(firstIndex == secondIndex)
        {
            return;
        }

        if(firstIndex < children.size() && secondIndex < children.size())
        {
            auto firstItDiff = children.begin();
            std::advance(firstItDiff, firstIndex);
            auto secondItDiff = children.begin();
            std::advance(secondItDiff, secondIndex);

            std::iter_swap(firstItDiff, secondItDiff);
        }
        else
        {
            std::cout << "Node::moveChild - index out of range!" << std::endl;
            return;
        }
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
} // namespace simple2dengine
