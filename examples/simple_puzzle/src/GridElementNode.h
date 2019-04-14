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

class GridElementNode : public simple2dengine::SpriteNode
{
  public:
    using SpriteNode::SpriteNode;
    virtual ~GridElementNode(){};

    virtual void onInput(sf::Event event) override;
    virtual void onUpdate(int deltaInMs) override;

    void setOnActivate(std::function<void(GridElementNode*)> activateAction);
    void setSelected(const bool isSelected);
    bool isSelected() const;

    void slideTo(const sf::Vector2f& whereToMovePosition);

  private:
    bool _isSelected = false;
    bool _isMoving = false;
    sf::Vector2f newPosition;

    const float speed = 0.7f;

    std::function<void(GridElementNode*)> onActivate;
};

#endif // _SIMPLE_PUZZLE_GRID_ELEMENT_NODE_H_
