/**
 * @file GridElementNode.h
 * @author Ilya Bardinov (ilya.bardinov@gmail.com)
 * @brief
 * @date 2019-03-26
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef _SIMPLE_PUZZLE_GRID_ELEMENT_NODE_H_
#define _SIMPLE_PUZZLE_GRID_ELEMENT_NODE_H_

#include <functional>

#include "simple2dengine/engine.h"
#include "simple2dengine/nodes/canvas/sprite_node.h"

using namespace simple2dengine;

enum class GridElementType : int
{
    None,
    Circle,
    Square,
    Triangle,
    Max
};

struct EnumClassHash
{
    template<typename T> std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

class GridElementNode : public simple2dengine::SpriteNode
{
    enum class State
    {
        None,
        Selected,
        Moving
    };

  public:
    using SpriteNode::SpriteNode;
    virtual ~GridElementNode(){};

    virtual void onInput(sf::Event event) override;
    virtual void onUpdate(int deltaInMs) override;

    void setType(const GridElementType type);
    GridElementType getType() const;

    void setState(const State state);
    State getState() const;

    void setSelected(const bool isSelected);

    const sf::Vector2f& getFuturePosition() const;

    void setOnActivate(const std::function<void(GridElementNode*)> activateAction);
    void setOnMovementFinished(const std::function<void(GridElementNode*)> movementFinishedAction);

    void slideTo(const sf::Vector2f& whereToMovePosition, bool moveBack = true);

  private:
    GridElementType type = GridElementType::None;
    State state = State::None;

    bool canMoveBack = false;
    sf::Vector2f futurePosition;

    const float speed = 1.0f;

    std::function<void(GridElementNode*)> onActivate;
    std::function<void(GridElementNode*)> onMovementFinished;
};

#endif // _SIMPLE_PUZZLE_GRID_ELEMENT_NODE_H_
