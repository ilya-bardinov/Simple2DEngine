#include <functional>
#include <random>
#include <chrono>

#include "GridNode.h"
#include "GridElementNode.h"

void GridNode::addElement(const std::string& pathToElement)
{
    engine.getAssetManager().load(pathToElement);
    elementsPathes.push_back(pathToElement);
}

void GridNode::generate(const uint8_t gridRows, const uint8_t gridColumns, const float gridElementsMargin)
{
    clear();

    float positionX = 0.0f;
    float positionY = 0.0f;

    const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    auto dice_rand = std::bind(std::uniform_int_distribution<int>(0, elementsPathes.size() - 1), std::mt19937(static_cast<unsigned int>(seed)));

    for(uint8_t row = 0; row < gridRows; ++row)
    {
        for(uint8_t column = 0; column < gridColumns; column++)
        {
            const int elementNumber = gridColumns * row + column;
            auto elementOfGrid = std::make_shared<GridElementNode>(engine, "element" + std::to_string(elementNumber));

            elementOfGrid->setImage(elementsPathes[dice_rand()]);
            elementOfGrid->setPosition(sf::Vector2f(positionX, positionY));
            elementOfGrid->setAnchor(simple2dengine::Anchor::Center);
            elementOfGrid->setOnActivate(std::bind(&GridNode::onElementActivated, this, std::placeholders::_1));

            if(column == gridColumns - 1)
            {
                positionY = positionY + gridElementsMargin + elementOfGrid->getGlobalBounds().height;
                positionX = 0.0f;
            }
            else
            {
                positionX = positionX + gridElementsMargin + elementOfGrid->getGlobalBounds().width;
            }

            addChild(std::move(elementOfGrid));
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
        // TODO: can I swap these elements?
        if(true)
        {
            selectedElement->setSelected(false);
            // swap their positions
            const sf::Vector2f selectedElementPosition = selectedElement->getPosition();
            selectedElement->slideTo(element->getPosition());
            element->slideTo(selectedElementPosition);

            selectedElement = nullptr;
        }
    }
}

void GridNode::onDestroy()
{
    for(const std::string& path : elementsPathes)
    {
        engine.getAssetManager().unload(path);
    }
}
