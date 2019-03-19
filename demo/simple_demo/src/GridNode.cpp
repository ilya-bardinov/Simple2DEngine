#include "GridNode.h"
#include "GridElementNode.h"

void GridNode::generate()
{
    printf("GridNode - generate\n");

    srand(static_cast<unsigned int>(time(0)));

    clear();

    float positionX = 0.0f;
    float positionY = 0.0f;
    for(int row = 0; row < gridRows; row++)
    {
        for(int column = 0; column < gridColumns; column++)
        {
            int elementNumber = gridColumns * row + column;
            auto elementOfGrid = std::make_shared<GridElementNode>(engine, "element" + std::to_string(elementNumber));

            int randNumber = rand() % 3;
            if(randNumber == 0)
                elementOfGrid->setImage("demo/simple_demo/assets/circle.png");
            else if(randNumber == 1)
                elementOfGrid->setImage("demo/simple_demo/assets/square.png");
            else
                elementOfGrid->setImage("demo/simple_demo/assets/triangle.png");

            elementOfGrid->setPosition(sf::Vector2f(positionX, positionY));
            elementOfGrid->setAnchor(simple2dengine::Anchor::Center);

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
