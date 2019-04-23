#include "GridElementNode.h"

void GridElementNode::onInput(sf::Event event)
{
    if(!onActivate || _isMoving)
        return;

    if(event.type == sf::Event::EventType::MouseButtonPressed)
    {
        if(event.mouseButton.button == sf::Mouse::Button::Left)
        {
            if(getGlobalBounds().contains(static_cast<float>(event.mouseButton.x),
                                          static_cast<float>(event.mouseButton.y)))
            {
                onActivate(this);
            }
        }
    }
}

void GridElementNode::onUpdate(int deltaInMs)
{
    if(_isMoving)
    {
        const sf::Vector2f newPositionDiff = getPosition() - newPosition;
        const int8_t signOfX = (newPositionDiff.x > 0) ? 1 : ((newPositionDiff.x < 0) ? -1 : 0);
        const int8_t signOfY = (newPositionDiff.y > 0) ? 1 : ((newPositionDiff.y < 0) ? -1 : 0);
        const float posDiff = speed * deltaInMs;

        if(newPositionDiff.x * signOfX <= posDiff && newPositionDiff.y * signOfY <= posDiff)
        {
            _isMoving = false;
            setPosition(newPosition);
            if(onMovementFinished && canMoveBack)
            {
                onMovementFinished(this);
            }
            return;
        }

        const sf::Vector2f vec(posDiff * signOfX, posDiff * signOfY);

        setPosition(getPosition() - vec);
    }
}

void GridElementNode::setType(GridElementType type)
{
    elementType = type;
}

GridElementType GridElementNode::getType()
{
    return elementType;
}

void GridElementNode::setOnActivate(std::function<void(GridElementNode*)> activateAction)
{
    onActivate = std::move(activateAction);
}

void GridElementNode::setOnMovementFinished(
    std::function<void(GridElementNode*)> movementFinishedAction)
{
    onMovementFinished = std::move(movementFinishedAction);
}

void GridElementNode::setSelected(const bool isSelected)
{
    if(isSelected)
    {
        setScale(0.9f, 0.9f);
        setColor(sf::Color(255, 255, 255, 128));
    }
    else
    {
        setScale(1.0f, 1.0f);
        setColor(sf::Color(255, 255, 255, 255));
    }

    this->_isSelected = isSelected;
}

bool GridElementNode::isSelected() const
{
    return _isSelected;
}

void GridElementNode::collapse()
{
    setScale(0.5f, 0.5f);
    setColor(sf::Color(255, 255, 255, 128));
}

void GridElementNode::slideTo(const sf::Vector2f& whereToMovePosition, bool moveBack /* = true*/)
{
    canMoveBack = moveBack;
    newPosition = whereToMovePosition;
    _isMoving = true;
}
