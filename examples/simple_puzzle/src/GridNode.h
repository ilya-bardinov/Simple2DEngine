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
#include <unordered_map>

#include "simple2dengine/engine.h"
#include "simple2dengine/nodes/canvas/canvas_node.h"

#include "GridElementNode.h"

using namespace simple2dengine;

struct GridParameters
{
    GridParameters(const uint8_t gridRows, const uint8_t gridColumns, const float gridElementsMargin)
        : rows(gridRows), columns(gridColumns), elementMargin(gridElementsMargin){};
    uint8_t rows = 0;
    uint8_t columns = 0;
    float elementMargin = 0.0f;
};

class GridNode : public simple2dengine::CanvasNode
{
  public:
    using CanvasNode::CanvasNode;
    GridNode(const std::string& name, const GridParameters& parameters);
    virtual ~GridNode(){};

    virtual void onCreate() override;
    virtual void onDestroy() override;

    // add texture to grid node
    void addElement(GridElementType elementType, const std::string& pathToElement);
    // generate grid of elements
    void generate();

  private:
    void generateTypeTable();
    void generateNodes();
    void onElementActivated(GridElementNode* element);
    void onMovementFinished(GridElementNode* element);

    bool canSwapElements(GridElementNode* element1, GridElementNode* element2) const;

    std::vector<unsigned int> findCollapsibleElementsHorizontally(const GridElementNode* element) const;
    std::vector<unsigned int> findCollapsibleElementsVertically(const GridElementNode* element) const;
    std::vector<unsigned int> findCollapsibleElements(const GridElementNode* element) const;
    void collapseElements(const std::vector<unsigned int>& elements);

    void swapElements(GridElementNode* element1, GridElementNode* element2, bool canMoveBack = true);
    void dropElement(GridElementNode* elementToDrop, GridElementNode* collapsedElement);

    std::unordered_map<GridElementType, std::string, EnumClassHash> elementsPathes;
    std::vector<GridElementType> elementTypeTable;

    GridElementNode* selectedElement = nullptr;
    GridElementNode* movementFinishedElement = nullptr;
    uint8_t gridRows = 0;
    uint8_t gridColumns = 0;
    float gridElementMargin = 0.0f;
};

#endif // _SIMPLE_PUZZLE_GRID_NODE_H_
