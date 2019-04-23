#include <string>

#include "GameScene.h"

#include "simple2dengine/nodes/canvas/sprite_node.h"

void GameScene::onCreate()
{
    engine->getAssetManager().load("examples/simple_puzzle/assets/font.ttf");

    // grid creation
    gridNode = std::make_shared<GridNode>("grid", GridParameters(gridRows, gridColumns, gridMargin));
    gridNode->addElement(GridElementType::Circle, "examples/simple_puzzle/assets/circle.png");
    gridNode->addElement(GridElementType::Square, "examples/simple_puzzle/assets/square.png");
    gridNode->addElement(GridElementType::Triangle, "examples/simple_puzzle/assets/triangle.png");
    addChild(gridNode);

    // just fps text
    fpsText = std::make_shared<simple2dengine::TextNode>("fpsText");
    fpsText->setFont(engine->getAssetManager(), "examples/simple_puzzle/assets/font.ttf");
    fpsText->setString("FPS: 0");
    fpsText->setPosition(sf::Vector2f(20, 20));
    fpsText->setFillColor(sf::Color(0, 0, 0));
    addChild(fpsText);
}

void GameScene::onEnter()
{
    // calculate position of grid node
    GridElementNode* elementOfGrid = new GridElementNode("element");
    elementOfGrid->setImage(engine->getAssetManager(), "examples/simple_puzzle/assets/circle.png");
    float gridPositionX =
        (engine->getConfiguration().window.width / 2.0f) -
        (((elementOfGrid->getGlobalBounds().width + gridMargin) * gridColumns - gridMargin) / 2.0f) +
        elementOfGrid->getGlobalBounds().width / 2;
    float gridPositionY =
        (engine->getConfiguration().window.height / 2.0f) -
        (((elementOfGrid->getGlobalBounds().height + gridMargin) * gridRows - gridMargin) / 2.0f) +
        elementOfGrid->getGlobalBounds().height / 2;
    delete elementOfGrid;

    gridNode->setPosition(sf::Vector2f(gridPositionX, gridPositionY));
    gridNode->generate();
}

void GameScene::onInput(sf::Event event)
{
    if(event.type == sf::Event::EventType::KeyPressed)
    {
        // regenerate grid by press 'Space' key
        if(event.key.code == sf::Keyboard::Space)
        {
            gridNode->generate();
        }
    }
}

void GameScene::onUpdate(int deltaInMs)
{
    if(fpsUpdateTimer >= fpsTimer)
    {
        fpsText->setString("FPS: " + std::to_string(1000 / deltaInMs));
        fpsUpdateTimer = 0;
    }
    fpsUpdateTimer += deltaInMs;
}

void GameScene::onDestroy()
{
    engine->getAssetManager().unload("examples/simple_puzzle/assets/font.ttf");
}
