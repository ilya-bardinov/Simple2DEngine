#include <chrono>
#include <functional>
#include <list>
#include <random>

#include "GridElementNode.h"
#include "GridNode.h"

GridNode::GridNode(const std::string& name, const GridParameters& parameters) : CanvasNode(name)
{
    this->gridElementMargin = parameters.elementMargin;
    this->gridRows = parameters.rows;
    this->gridColumns = parameters.columns;
}

void GridNode::addElement(GridElementType elementType, const std::string& pathToElement)
{
    elementsPathes[elementType] = pathToElement;
}

void GridNode::onCreate()
{
    for(const auto& element : elementsPathes)
    {
        engine->getAssetManager().load(element.second);
    }
}

void GridNode::generate()
{
    clear();
    elementTypeTable.clear();
    float positionX = 0.0f;
    float positionY = 0.0f;

    // we need random element filling
    const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    auto dice_rand =
        std::bind(std::uniform_int_distribution<int>(static_cast<int>(GridElementType::None) + 1,
                                                     static_cast<int>(GridElementType::Max) - 1),
                  std::mt19937(static_cast<unsigned int>(seed)));

    // generate table with element's types
    for(uint8_t row = 0; row < gridRows; ++row)
    {
        for(uint8_t column = 0; column < gridColumns; ++column)
        {
            const int elementNumber = gridColumns * row + column;
            GridElementType randType = static_cast<GridElementType>(dice_rand());
            while((column >= 2 &&
                   elementTypeTable[elementNumber - 2] == elementTypeTable[elementNumber - 1] &&
                   elementTypeTable[elementNumber - 1] == randType) ||
                  (row >= 2 &&
                   elementTypeTable[elementNumber - 2 * gridColumns] ==
                       elementTypeTable[elementNumber - gridColumns] &&
                   elementTypeTable[elementNumber - gridColumns] == randType))
            {
                randType = static_cast<GridElementType>(dice_rand());
            }
            elementTypeTable.push_back(randType);
        }
    }

    // geenrate nodes with type table from above
    for(uint8_t row = 0; row < gridRows; ++row)
    {
        for(uint8_t column = 0; column < gridColumns; ++column)
        {
            const int elementNumber = gridColumns * row + column;
            auto elementOfGrid =
                std::make_shared<GridElementNode>("element" + std::to_string(elementNumber));

            GridElementType elementType = elementTypeTable[elementNumber];

            elementOfGrid->setImage(engine->getAssetManager(), elementsPathes[elementType]);
            elementOfGrid->setType(elementType);
            elementOfGrid->setPosition(sf::Vector2f(positionX, positionY));
            elementOfGrid->setAnchor(simple2dengine::Anchor::Center);
            elementOfGrid->setOnActivate(
                std::bind(&GridNode::onElementActivated, this, std::placeholders::_1));
            elementOfGrid->setOnMovementFinished(
                std::bind(&GridNode::onMovementFinished, this, std::placeholders::_1));

            if(column == gridColumns - 1)
            {
                positionY += gridElementMargin + elementOfGrid->getGlobalBounds().height;
                positionX = 0.0f;
            }
            else
            {
                positionX += gridElementMargin + elementOfGrid->getGlobalBounds().width;
            }

            addChild(std::move(elementOfGrid));
        }
    }
}

bool GridNode::canSwapElements(GridElementNode* element1, GridElementNode* element2) const
{
    const unsigned int index1 = element1->getIndex();
    const unsigned int index2 = element2->getIndex();

    const unsigned int diff = (index1 > index2) ? index1 - index2 : index2 - index1;

    if(diff == 1)
    {
        if(std::max(index1, index2) % gridColumns != 0)
        {
            return true;
        }
    }
    else if(diff == gridColumns)
    {
        return true;
    }

    return false;
}

void GridNode::swapElements(GridElementNode* element1, GridElementNode* element2,
                            bool canMoveBack /*= true*/)
{
    const sf::Vector2f elementPosition1 = element1->getPosition();
    element1->slideTo(element2->getPosition(), canMoveBack);
    element2->slideTo(elementPosition1, canMoveBack);

    GridElementType elementType1 = elementTypeTable[element1->getIndex()];
    elementTypeTable[element1->getIndex()] = elementTypeTable[element2->getIndex()];
    elementTypeTable[element2->getIndex()] = elementType1;

    swap(element1->getIndex(), element2->getIndex());
}

bool GridNode::collapseNearbyElements(GridElementNode* element)
{
    bool canCollapse = false;

    const unsigned int index = element->getIndex();
    std::list<unsigned int> listOfCollapsible;
    listOfCollapsible.push_back(index);

    const unsigned int columnIndexStart = static_cast<int>(std::floor(index / gridColumns));

    // try to find elements in element's row
    if(index > 0)
    {
        for(unsigned int indexByRow = index - 1; indexByRow >= columnIndexStart * gridColumns;
            --indexByRow)
        {
            if(elementTypeTable[indexByRow] == elementTypeTable[index])
            {
                listOfCollapsible.push_back(indexByRow);
            }
            else
            {
                break;
            }
        }
    }
    for(unsigned int indexByRow = index + 1; indexByRow < (columnIndexStart + 1) * gridColumns;
        ++indexByRow)
    {
        if(elementTypeTable[indexByRow] == elementTypeTable[index])
        {
            listOfCollapsible.push_back(indexByRow);
        }
        else
        {
            break;
        }
    }

    // collapse elements
    if(listOfCollapsible.size() >= 3)
    {
        canCollapse = true;
        while(listOfCollapsible.size() > 0)
        {
            const unsigned int collapsibleIndex = listOfCollapsible.front();
            std::shared_ptr<GridElementNode> collapsibleElement =
                std::dynamic_pointer_cast<GridElementNode>(getChild(collapsibleIndex));
            listOfCollapsible.pop_front();
            if(collapsibleElement != nullptr)
            {
                collapsibleElement->collapse();
                unsigned int movementIndex = collapsibleIndex;
                while(movementIndex >= gridColumns)
                {
                    movementIndex -= gridColumns;

                    std::shared_ptr<GridElementNode> elementAbove =
                        std::dynamic_pointer_cast<GridElementNode>(getChild(movementIndex));

                    elementAbove->slideTo(collapsibleElement->getPosition(), false);
                    collapsibleElement->setPosition(elementAbove->getPosition());

                    GridElementType elementType1 = elementTypeTable[elementAbove->getIndex()];
                    elementTypeTable[elementAbove->getIndex()] =
                        elementTypeTable[collapsibleElement->getIndex()];
                    elementTypeTable[collapsibleElement->getIndex()] = elementType1;

                    swap(collapsibleElement->getIndex(), elementAbove->getIndex());
                }
            }
        }
    }
    listOfCollapsible.clear();

    return canCollapse;
}

void GridNode::onElementActivated(GridElementNode* element)
{
    if(!element)
    {
        return;
    }

    if(!selectedElement)
    {
        selectedElement = element;
        element->setSelected(true);
    }
    else if(selectedElement == element)
    {
        selectedElement = nullptr;
        element->setSelected(false);
    }
    else
    {
        if(canSwapElements(selectedElement, element))
        {
            selectedElement->setSelected(false);
            // swap their positions
            swapElements(selectedElement, element);

            selectedElement = nullptr;
        }
    }
}

void GridNode::onMovementFinished(GridElementNode* element)
{
    if(!element)
    {
        return;
    }

    if(!movementFinishedElement)
    {
        movementFinishedElement = element;
    }
    else
    {
        if(!collapseNearbyElements(movementFinishedElement) && !collapseNearbyElements(element))
        {
            // swap their positions back
            swapElements(movementFinishedElement, element, false);
        }
        movementFinishedElement = nullptr;
    }
}

void GridNode::onDestroy()
{
    for(const auto& element : elementsPathes)
    {
        engine->getAssetManager().unload(element.second);
    }
}
