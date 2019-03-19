#include <string>

#include "GameScene.h"

#include "simple2dengine/nodes/canvas/sprite_node.h"

void GameScene::onCreate()
{
    printf("GameScene - onCreate\n");

    engine.getAssetManager().load("demo/simple_demo/assets/font.ttf");
    engine.getAssetManager().load("demo/simple_demo/assets/circle.png");
    engine.getAssetManager().load("demo/simple_demo/assets/square.png");
    engine.getAssetManager().load("demo/simple_demo/assets/triangle.png");

    gridNode = std::make_shared<GridNode>(engine, "grid");
    gridNode->setPosition(sf::Vector2f(100, 100));
    addChild(gridNode);
    gridNode->generate();

    fpsText = std::make_shared<simple2dengine::TextNode>(engine, "fpsText");
    fpsText->setFont("demo/simple_demo/assets/font.ttf");
    fpsText->setString("FPS: 0");
    fpsText->setPosition(sf::Vector2f(20, 20));
    addChild(fpsText);
}

void GameScene::onEnter()
{
    printf("GameScene - onEnter\n");
}

void GameScene::onInput(sf::Event event)
{
    if(event.type == sf::Event::EventType::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Space)
        {
            gridNode->generate();
        }
    }
}

void GameScene::onUpdate(int deltaInMs)
{
    fpsText->setString("FPS: " + std::to_string(1000 / deltaInMs));
}

void GameScene::onExit()
{
    printf("GameScene - onExit\n");
}

void GameScene::onDestroy()
{
    printf("GameScene - onDestroy\n");

    engine.getAssetManager().unload("demo/simple_demo/assets/font.ttf");
    engine.getAssetManager().unload("demo/simple_demo/assets/circle.png");
    engine.getAssetManager().unload("demo/simple_demo/assets/square.png");
    engine.getAssetManager().unload("demo/simple_demo/assets/triangle.png");
}
