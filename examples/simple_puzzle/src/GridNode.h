/**
 * @file GridNode.h
 * @author Ilya Bardinov (ilya.bardinov@gmail.com)
 * @brief
 * @date 2019-03-26
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef _SIMPLE_PUZZLE_GRID_NODE_H_
#define _SIMPLE_PUZZLE_GRID_NODE_H_

#include <string>
#include <vector>

#include "simple2dengine/engine.h"
#include "simple2dengine/nodes/canvas/canvas_node.h"

#include "GridElementNode.h"

using namespace simple2dengine;

class GridNode : public simple2dengine::CanvasNode
{
  public:
    using CanvasNode::CanvasNode;
    virtual ~GridNode(){};

    virtual void onCreate() override;
    virtual void onDestroy() override;

    // add texture to grid node
    void addElement(const std::string& pathToElement);
    // generate grid of elements
    void generate(const uint8_t gridRows, const uint8_t gridColumns, const float gridElementsMargin);

  private:
    void onElementActivated(GridElementNode* element);

    std::vector<std::string> elementsPathes;

    GridElementNode* selectedElement = nullptr;
};

#endif // _SIMPLE_PUZZLE_GRID_NODE_H_
