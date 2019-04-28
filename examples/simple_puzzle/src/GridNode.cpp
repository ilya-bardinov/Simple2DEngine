#include <chrono>
#include <functional>
#include <list>
#include <random>

#include "GridElementNode.h"
#include "GridNode.h"

GridNode::GridNode(const std::string& _name, const GridParameters& parameters) : CanvasNode(_name)
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
    // generate table with random element's types
    generateTypeTable();
    // geenrate nodes with type table from above
    generateNodes();
}

void GridNode::generateTypeTable()
{
    elementTypeTable.clear();

    // we need random element filling
    const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    auto dice_rand = std::bind(std::uniform_int_distribution<int>(static_cast<int>(GridElementType::None) + 1,
                                                                  static_cast<int>(GridElementType::Max) - 1),
                               std::mt19937(static_cast<unsigned int>(seed)));

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
}

void GridNode::generateNodes()
{
    // remove all children
    clear();

    float positionX = 0.0f;
    float positionY = 0.0f;

    for(uint8_t row = 0; row < gridRows; ++row)
    {
        for(uint8_t column = 0; column < gridColumns; ++column)
        {
            const int elementNumber = gridColumns * row + column;
            auto elementOfGrid = std::make_shared<GridElementNode>("element" + std::to_string(elementNumber));

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

void GridNode::swapElements(GridElementNode* element1, GridElementNode* element2, bool canMoveBack /*= true*/)
{
    const sf::Vector2f elementPosition1 = element1->getPosition();
    element1->slideTo(element2->getPosition(), canMoveBack);
    element2->slideTo(elementPosition1, canMoveBack);

    GridElementType elementType1 = elementTypeTable[element1->getIndex()];
    elementTypeTable[element1->getIndex()] = elementTypeTable[element2->getIndex()];
    elementTypeTable[element2->getIndex()] = elementType1;

    swap(element1->getIndex(), element2->getIndex());
}

void GridNode::dropElement(GridElementNode* elementToDrop, GridElementNode* collapsedElement)
{
    const sf::Vector2f futurePosOfDropElement = elementToDrop->getFuturePosition();
    elementToDrop->slideTo(collapsedElement->getPosition(), false);
    collapsedElement->setPosition(futurePosOfDropElement);

    GridElementType elementType1 = elementTypeTable[elementToDrop->getIndex()];
    elementTypeTable[elementToDrop->getIndex()] = elementTypeTable[collapsedElement->getIndex()];
    elementTypeTable[collapsedElement->getIndex()] = elementType1;

    swap(collapsedElement->getIndex(), elementToDrop->getIndex());
}

std::vector<unsigned int> GridNode::findCollapsibleElements(const GridElementNode* element) const
{
    std::vector<unsigned int> collapsibleHorizontal = findCollapsibleElementsHorizontally(element);
    std::vector<unsigned int> collapsibleVertical = findCollapsibleElementsVertically(element);

    collapsibleHorizontal.insert(collapsibleHorizontal.end(), collapsibleVertical.begin(),
                                 collapsibleVertical.end());

    return collapsibleHorizontal;
}

std::vector<unsigned int> GridNode::findCollapsibleElementsHorizontally(const GridElementNode* element) const
{
    const unsigned int index = element->getIndex();
    std::vector<unsigned int> listOfCollapsible;
    listOfCollapsible.push_back(index);

    const unsigned int elementColumn = static_cast<int>(std::floor(index / gridColumns));

    // try to find going left from element
    if(index > 0)
    {
        unsigned int rowIndex = index - 1;
        while(rowIndex >= elementColumn * gridColumns)
        {
            if(elementTypeTable[rowIndex] == elementTypeTable[index])
            {
                listOfCollapsible.push_back(rowIndex);
            }
            else
            {
                break;
            }
            if(rowIndex == 0)
                break;
            rowIndex--;
        }
    }

    // try to find going right from element
    unsigned int rowIndex = index + 1;
    while(rowIndex < (elementColumn + 1) * gridColumns)
    {

        if(elementTypeTable[rowIndex] == elementTypeTable[index])
        {
            listOfCollapsible.push_back(rowIndex);
        }
        else
        {
            break;
        }
        rowIndex++;
    }

    if(listOfCollapsible.size() < 3)
    {
        listOfCollapsible.clear();
    }

    return listOfCollapsible;
}

std::vector<unsigned int> GridNode::findCollapsibleElementsVertically(const GridElementNode* element) const
{
    const unsigned int index = element->getIndex();
    std::vector<unsigned int> listOfCollapsible;
    listOfCollapsible.push_back(index);

    // try to find going up from element
    unsigned int columnIndex = index;
    while(columnIndex >= gridColumns)
    {
        columnIndex -= gridColumns;
        if(elementTypeTable[columnIndex] == elementTypeTable[index])
        {
            listOfCollapsible.push_back(columnIndex);
        }
        else
        {
            break;
        }
    }

    // try to find going down from element
    columnIndex = index + gridColumns;
    while(columnIndex < gridRows * gridColumns)
    {
        if(elementTypeTable[columnIndex] == elementTypeTable[index])
        {
            listOfCollapsible.push_back(columnIndex);
        }
        else
        {
            break;
        }
        columnIndex += gridColumns;
    }

    if(listOfCollapsible.size() < 3)
    {
        listOfCollapsible.clear();
    }

    return listOfCollapsible;
}

void GridNode::collapseElements(const std::vector<unsigned int>& elements)
{
    // prepare rand func
    const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    auto dice_rand = std::bind(std::uniform_int_distribution<int>(static_cast<int>(GridElementType::None) + 1,
                                                                  static_cast<int>(GridElementType::Max) - 1),
                               std::mt19937(static_cast<unsigned int>(seed)));

    for(unsigned int elementIndex : elements)
    {
        std::shared_ptr<GridElementNode> element =
            std::dynamic_pointer_cast<GridElementNode>(getChild(elementIndex));

        if(element != nullptr)
        {
            unsigned int aboveElementIndex = elementIndex;
            std::shared_ptr<GridElementNode> aboveElement = element;
            while(aboveElementIndex >= gridColumns)
            {
                aboveElementIndex -= gridColumns;

                aboveElement = std::dynamic_pointer_cast<GridElementNode>(getChild(aboveElementIndex));

                if(aboveElement)
                {
                    dropElement(aboveElement.get(), element.get());
                }
            }

            // set new position for collapsed element
            const sf::Vector2f aboveElementPosition = aboveElement->getPosition();
            const sf::Vector2f elementPosition = element->getPosition();
            element->setPosition(
                sf::Vector2f(aboveElementPosition.x,
                             aboveElementPosition.y - element->getGlobalBounds().height - gridElementMargin));

            element->slideTo(elementPosition, false);

            // change element's type
            GridElementType randType = static_cast<GridElementType>(dice_rand());
            element->setImage(engine->getAssetManager(), elementsPathes[randType]);
            element->setType(randType);
            elementTypeTable[element->getIndex()] = randType;
        }
    }
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
        std::vector<unsigned int> collapsibleElements = findCollapsibleElements(movementFinishedElement);
        std::vector<unsigned int> collapsibleElementsSecond = findCollapsibleElements(element);
        collapsibleElements.insert(collapsibleElements.end(), collapsibleElementsSecond.begin(),
                                   collapsibleElementsSecond.end());

        std::sort(collapsibleElements.begin(), collapsibleElements.end());
        collapsibleElements.erase(std::unique(collapsibleElements.begin(), collapsibleElements.end()),
                                  collapsibleElements.end());

        if(collapsibleElements.size() == 0)
        {
            // swap their positions back
            swapElements(movementFinishedElement, element, false);
        }
        else
        {
            collapseElements(std::move(collapsibleElements));
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
