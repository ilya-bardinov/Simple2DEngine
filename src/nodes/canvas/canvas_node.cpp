#include "simple2dengine/nodes/canvas/canvas_node.h"

namespace simple2dengine
{
    void CanvasNode::setPosition(const sf::Vector2f& _position)
    {
        globalPosition = globalPosition - this->position + _position;

        for(auto& child : getChildren())
        {
            CanvasNode* childPtr = dynamic_cast<CanvasNode *>(child.get());
            if(childPtr)
            {
		        childPtr->globalPosition = globalPosition + childPtr->position;
                childPtr->setPosition(childPtr->getPosition());
	        }
        }

        this->position = _position;

        updateTransform();
    }

    void CanvasNode::move(const sf::Vector2f& _position)
    {
        setPosition(position + _position);
    }

    const sf::Vector2f& CanvasNode::getPosition() const
    {
        return position;
    }

    const sf::Vector2f& CanvasNode::getGlobalPosition() const
    {
        return globalPosition;
    }

    void CanvasNode::setVisible(bool isVisible)
    {
        this->visible = isVisible;
    }

    bool CanvasNode::isVisible() const
    {
        return visible;
    }

    bool CanvasNode::isVisibleInTree() const
    {
        const CanvasNode* rootPtr = this;

        while(rootPtr)
        {
		    if (!rootPtr->visible)
			    return false;
		    rootPtr = dynamic_cast<CanvasNode *>(rootPtr->getParent().get());
	    }

        return true;
    }

    void CanvasNode::setAnchor(const Anchor nodeAnchor)
    {
        anchor = nodeAnchor;

        updateTransform();
    }

    Anchor CanvasNode::getAnchor() const
    {
        return anchor;
    }

    void CanvasNode::updateTransform() { }
} // simple2dengine
