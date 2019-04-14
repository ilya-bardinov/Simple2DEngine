#include <string>

#include "GameScene.h"

#include "simple2dengine/nodes/canvas/sprite_node.h"

void GameScene::onCreate()
{
    engine->getAssetManager().load("examples/simple_puzzle/assets/font.ttf");

    // grid creation
    gridNode = std::make_shared<GridNode>("grid");
    gridNode->addElement("examples/simple_puzzle/assets/circle.png");
    gridNode->addElement("examples/simple_puzzle/assets/square.png");
    gridNode->addElement("examples/simple_puzzle/assets/triangle.png");
    addChild(gridNode);

    gridNode->setPosition(sf::Vector2f(100, 100));
    gridNode->generate(gridRows, gridColumns, gridMargin);

    // just fps text
    fpsText = std::make_shared<simple2dengine::TextNode>("fpsText");
    fpsText->setFont(engine->getAssetManager(), "examples/simple_puzzle/assets/font.ttf");
    fpsText->setString("FPS: 0");
    fpsText->setPosition(sf::Vector2f(20, 20));
    fpsText->setFillColor(sf::Color(0, 0, 0));
    addChild(fpsText);
}

void GameScene::onInput(sf::Event event)
{
    if(event.type == sf::Event::EventType::KeyPressed)
    {
        // regenerate grid by press 'Space' key
        if(event.key.code == sf::Keyboard::Space)
        {
            gridNode->generate(gridRows, gridColumns, gridMargin);
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
