#include "GridElementNode.h"

void GridElementNode::onInput(sf::Event event)
{
    if(!onActivate || state == State::Moving)
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
    if(state == State::Moving)
    {
        if(deltaInMs <= 0)
        {
            deltaInMs = 1;
        }

        const sf::Vector2f newPositionDiff = getPosition() - futurePosition;
        const int8_t signOfX = (newPositionDiff.x > 0) ? 1 : ((newPositionDiff.x < 0) ? -1 : 0);
        const int8_t signOfY = (newPositionDiff.y > 0) ? 1 : ((newPositionDiff.y < 0) ? -1 : 0);
        const float posDiff = speed * deltaInMs;

        if(newPositionDiff.x * signOfX <= posDiff && newPositionDiff.y * signOfY <= posDiff)
        {
            state = State::None;
            setPosition(futurePosition);
            if(onMovementFinished && canMoveBack)
            {
                onMovementFinished(this);
            }
            return;
        }

        const sf::Vector2f vec(posDiff * signOfX, posDiff * signOfY);

        move(-vec);
    }
}

void GridElementNode::setType(const GridElementType _type)
{
    this->type = _type;
}

GridElementType GridElementNode::getType() const
{
    return type;
}

void GridElementNode::setState(const State _state)
{
    this->state = _state;
}

GridElementNode::State GridElementNode::getState() const
{
    return state;
}

const sf::Vector2f& GridElementNode::getFuturePosition() const
{
    if(state == State::Moving)
    {
        return futurePosition;
    }
    else
    {
        return getPosition();
    }
}

void GridElementNode::setOnActivate(std::function<void(GridElementNode*)> activateAction)
{
    onActivate = std::move(activateAction);
}

void GridElementNode::setOnMovementFinished(std::function<void(GridElementNode*)> movementFinishedAction)
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

    state = State::Selected;
}

void GridElementNode::slideTo(const sf::Vector2f& whereToMovePosition, bool moveBack /* = true*/)
{
    canMoveBack = moveBack;
    futurePosition = whereToMovePosition;
    state = State::Moving;
}
