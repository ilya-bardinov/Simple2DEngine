#include <chrono>
#include <functional>
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
    float positionX = 0.0f;
    float positionY = 0.0f;

    // we need random element filling
    const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    auto dice_rand =
        std::bind(std::uniform_int_distribution<int>(static_cast<int>(GridElementType::None) + 1,
                                                     static_cast<int>(GridElementType::Max) - 1),
                  std::mt19937(static_cast<unsigned int>(seed)));

    std::vector<GridElementType> elementTypeTable;
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

bool GridNode::canSwapElements(GridElementNode* element1, GridElementNode* element2)
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
            const sf::Vector2f selectedElementPosition = selectedElement->getPosition();
            selectedElement->slideTo(element->getPosition());
            element->slideTo(selectedElementPosition);

            swap(element->getIndex(), selectedElement->getIndex());

            selectedElement = nullptr;
        }
    }
}

void GridNode::onDestroy()
{
    for(const auto& element : elementsPathes)
    {
        engine->getAssetManager().unload(element.second);
    }
}
