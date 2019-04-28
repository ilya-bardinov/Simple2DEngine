#include "catch.hpp"
#include "simple2dengine/configuration.h"
#include "simple2dengine/engine.h"
#include "simple2dengine/managers/scene_manager.h"
#include "simple2dengine/nodes/canvas/canvas_node.h"
#include "simple2dengine/nodes/canvas/sprite_node.h"
#include "simple2dengine/nodes/canvas/text_node.h"
#include "simple2dengine/nodes/music_node.h"
#include "simple2dengine/nodes/node.h"

SCENARIO("Scenes can be added, activated and deleted")
{

    GIVEN("Engine with scene manager")
    {
        std::vector<int> v(5);
        simple2dengine::Configuration config;
        config.framerate.verticalSync = true;
        config.window.width = 400;
        config.window.height = 300;
        config.window.name = std::string("Unit Test");
        simple2dengine::Engine engine(config);

        simple2dengine::SceneManager scenemanager = engine.getSceneManager();

        REQUIRE(scenemanager.getSceneCount() == 0);

        WHEN("Remove non-existed scene")
        {
            scenemanager.activateScene("test_scene");
            scenemanager.removeScene("test_scene");
            scenemanager.activateScene("test_scene");

            THEN("the size changes")
            {
                REQUIRE(scenemanager.getSceneCount() == 0);
            }
        }

        WHEN("Clear scene")
        {
            auto node = std::make_shared<simple2dengine::Node>("test_scene");
            scenemanager.addScene(node);
            scenemanager.activateScene("test_scene");
            scenemanager.clear();

            THEN("the size changes")
            {
                REQUIRE(scenemanager.getSceneCount() == 1);
            }
        }

        WHEN("Add and delete scene")
        {
            auto node = std::make_shared<simple2dengine::Node>("test_scene");
            scenemanager.addScene(node);
            scenemanager.activateScene("test_scene");

            THEN("the size changes when added")
            {
                REQUIRE(scenemanager.getSceneCount() == 1);
            }

            scenemanager.removeScene("test_scene");
            scenemanager.activateScene("test_scene");

            THEN("the size changes when deleted")
            {
                REQUIRE(scenemanager.getSceneCount() == 0);
            }

            scenemanager.addScene(node);

            THEN("the size changes when added")
            {
                REQUIRE(scenemanager.getSceneCount() == 1);
            }

            scenemanager.removeScene("test_scene");

            THEN("the size changes when deleted")
            {
                REQUIRE(scenemanager.getSceneCount() == 0);
            }
        }

        WHEN("Add multiple nodes to scene")
        {
            auto scene = std::make_shared<simple2dengine::Node>("simple_scene");
            scenemanager.addScene(scene);
            scenemanager.activateScene("simple_scene");

            auto layer_1_node_1 = std::make_shared<simple2dengine::Node>("layer_1_node_1");
            scene->addChild(layer_1_node_1);
            auto layer_1_node_2 = std::make_shared<simple2dengine::CanvasNode>("layer_1_node_2");
            scene->addChild(layer_1_node_2);
            auto layer_1_node_3 = std::make_shared<simple2dengine::Node>("layer_1_node_3");
            scene->addChild(layer_1_node_3);
            auto layer_1_node_4 = std::make_shared<simple2dengine::MusicNode>("layer_1_node_4");
            scene->addChild(layer_1_node_4);

            auto layer_2_node_1 = std::make_shared<simple2dengine::SpriteNode>("layer_2_node_1");
            layer_1_node_2->addChild(layer_2_node_1);
            auto layer_2_node_2 = std::make_shared<simple2dengine::CanvasNode>("layer_2_node_2");
            layer_1_node_2->addChild(layer_2_node_2);

            auto layer_3_node_1 = std::make_shared<simple2dengine::TextNode>("layer_3_node_1");
            layer_2_node_2->addChild(layer_3_node_1);

            THEN("the size changes")
            {
                REQUIRE(scenemanager.getSceneCount() == 1);
                REQUIRE(scene->getChildren().size() == 4);
                REQUIRE(layer_1_node_2->getChildren().size() == 2);
                REQUIRE(layer_2_node_2->getChildren().size() == 1);
                REQUIRE(layer_1_node_3->getChildren().size() == 0);
                REQUIRE(layer_3_node_1->getChildren().size() == 0);
            }

            THEN("name is correct")
            {
                REQUIRE(scene->getName() == "simple_scene");
                REQUIRE(layer_1_node_3->getName() == "layer_1_node_3");
                REQUIRE(layer_1_node_2->getName() == "layer_1_node_2");
            }

            THEN("root is correct")
            {
                REQUIRE(scene->getRoot() == scene);
                REQUIRE(layer_1_node_2->getRoot() == scene);
                REQUIRE(layer_3_node_1->getRoot() == scene);
            }

            THEN("parent is correct")
            {
                REQUIRE(scene->getParent() == nullptr);
                REQUIRE(layer_1_node_2->getParent() == scene);
                REQUIRE(layer_3_node_1->getParent() == layer_2_node_2);
            }

            THEN("getting nodes is correct")
            {
                REQUIRE(scene->getNode("/") == scene);
                REQUIRE(scene->getNode("/layer_1_node_1") == layer_1_node_1);
                REQUIRE(scene->getNode("/layer_1_node_1/") == layer_1_node_1);
                REQUIRE(scene->getNode("layer_1_node_1/layer_3_node_1") == nullptr);
                REQUIRE(scene->getNode("layer_1_node_2/layer_2_node_2") == layer_2_node_2);
                REQUIRE(layer_2_node_2->getNode("/") == scene);
                REQUIRE(layer_2_node_2->getNode("/layer_1_node_1") == layer_1_node_1);
                REQUIRE(layer_2_node_2->getNode("layer_1_node_1") == nullptr);
                REQUIRE(layer_2_node_2->getNode("layer_3_node_1") == layer_3_node_1);
                REQUIRE(layer_2_node_2->getNode(".") == layer_2_node_2);
                REQUIRE(layer_2_node_2->getNode("..") == layer_1_node_2);
                REQUIRE(layer_2_node_2->getNode("../../layer_1_node_1") == layer_1_node_1);
            }

            layer_1_node_2->setPosition(sf::Vector2f(10.0f, 10.0f));
            layer_2_node_2->setPosition(sf::Vector2f(20.0f, 20.0f));
            layer_2_node_2->setVisible(false);

            THEN("position and visibility are correct")
            {
                REQUIRE(layer_1_node_2->getPosition() == sf::Vector2f(10.0f, 10.0f));
                REQUIRE(layer_2_node_2->getGlobalPosition() == sf::Vector2f(30.0f, 30.0f));
                REQUIRE(layer_3_node_1->getGlobalPosition() == sf::Vector2f(30.0f, 30.0f));
                REQUIRE(layer_3_node_1->getPosition() == sf::Vector2f(0.0f, 0.0f));
                REQUIRE(layer_2_node_2->isVisible() == false);
                REQUIRE(layer_2_node_2->isVisibleInTree() == false);
                REQUIRE(layer_3_node_1->isVisible() == true);
                REQUIRE(layer_3_node_1->isVisibleInTree() == false);
            }

            layer_1_node_2->removeChild(layer_1_node_2->getChild("layer_2_node_2"));

            THEN("the size changes")
            {
                REQUIRE(scenemanager.getSceneCount() == 1);
                REQUIRE(scene->getChildren().size() == 4);
                REQUIRE(layer_1_node_2->getChildren().size() == 1);
                REQUIRE(layer_2_node_2->getChildren().size() == 1);
                REQUIRE(layer_1_node_3->getChildren().size() == 0);
                REQUIRE(layer_3_node_1->getChildren().size() == 0);
            }

            engine.getAssetManager().load("assets/player.png");
            engine.getAssetManager().unload("assets/player.png");
            engine.getAssetManager().load("assets/sound.wav");
            layer_2_node_1->setImage(engine.getAssetManager(), "assets/player.png");
            layer_3_node_1->setFont(engine.getAssetManager(), "assets/font.ttf");
            layer_3_node_1->setFont(engine.getAssetManager(), "assets/font.ttf");
            layer_1_node_4->openFromFile("assets/sound.wav");

            THEN("unload resources")
            {
                engine.getAssetManager().unload("assets/player.png");
                engine.getAssetManager().unload("assets/font.ttf");
            }
        }

        WHEN("Add multiple scenes")
        {
            auto scene_1 = std::make_shared<simple2dengine::Node>("scene_1");
            scenemanager.addScene(scene_1);
            auto scene_2 = std::make_shared<simple2dengine::Node>("scene_2");
            scenemanager.addScene(scene_2);
            auto scene_3 = std::make_shared<simple2dengine::Node>("scene_3");
            scenemanager.addScene(scene_3);
            auto scene_4 = std::make_shared<simple2dengine::Node>("scene_4");
            scenemanager.addScene(scene_4);

            THEN("the size changes")
            {
                REQUIRE(scenemanager.getSceneCount() == 4);
            }

            scenemanager.activateScene("scene_3");

            scenemanager.removeScene("scene_3");
            scenemanager.removeScene("scene_2");
            scenemanager.activateScene("scene_4");

            THEN("the size changes")
            {
                REQUIRE(scenemanager.getSceneCount() == 2);
            }

            engine.stop();
        }
    }
}
