// Let Catch provide main():
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "simple2dengine/engine.h"
#include "simple2dengine/configuration.h"
#include "simple2dengine/nodes/node.h"
#include "simple2dengine/managers/scene_manager.h"

TEST_CASE("State of window in Engine") {

    simple2dengine::Configuration config;
    config.fps = 60;
    config.window.width = 400;
    config.window.height = 300;
    config.window.name = std::string("Unit Test");
    simple2dengine::Engine engine(config);
    engine.stop();
}

TEST_CASE("Work of scenes in Engine") {
    simple2dengine::Configuration config;
    config.fps = 60;
    config.window.width = 400;
    config.window.height = 300;
    config.window.name = std::string("Unit Test");
    simple2dengine::Engine engine(config);

    simple2dengine::SceneManager scenemanager = engine.getSceneManager();

    SECTION("Scenes count") {

        REQUIRE(scenemanager.getSceneCount() == 0);
    }
    SECTION("Add, switch and remove scene") {
        std::shared_ptr<simple2dengine::Node> node = std::make_shared<simple2dengine::Node>(engine);
        scenemanager.addScene("root", node);
        scenemanager.switchToScene("root");

        REQUIRE(scenemanager.getSceneCount() == 1);

        scenemanager.removeScene("root");

        REQUIRE(scenemanager.getSceneCount() == 0);

        scenemanager.switchToScene("root");

        REQUIRE(scenemanager.getSceneCount() == 0);
    }
    SECTION("Add and remove scene") {
        std::shared_ptr<simple2dengine::Node> node = std::make_shared<simple2dengine::Node>(engine);
        scenemanager.addScene("root", node);

        REQUIRE(scenemanager.getSceneCount() == 1);

        scenemanager.removeScene("root");

        REQUIRE(scenemanager.getSceneCount() == 0);

        scenemanager.switchToScene("root");

        REQUIRE(scenemanager.getSceneCount() == 0);
    }
    SECTION("Remove scene without adding it") {
        std::shared_ptr<simple2dengine::Node> node = std::make_shared<simple2dengine::Node>(engine);

        scenemanager.removeScene("root");

        REQUIRE(scenemanager.getSceneCount() == 0);

        scenemanager.switchToScene("root");

        REQUIRE(scenemanager.getSceneCount() == 0);
    }
    SECTION("Multiple nodes") {
        printf("[STARTED] Multiple nodes \n");
        std::shared_ptr<simple2dengine::Node> node1 = std::make_shared<simple2dengine::Node>(engine);
        std::shared_ptr<simple2dengine::Node> node2 = std::make_shared<simple2dengine::Node>(engine);

        scenemanager.addScene("root", node1);
        scenemanager.addScene("menu", node2);

        REQUIRE(scenemanager.getSceneCount() == 2);

        scenemanager.switchToScene("root");

        REQUIRE(scenemanager.getSceneCount() == 2);

        std::shared_ptr<simple2dengine::Node> childNode1 = std::make_shared<simple2dengine::Node>(engine);
        std::shared_ptr<simple2dengine::Node> childNode2 = std::make_shared<simple2dengine::Node>(engine);
        node2->addChild(childNode1);
        node2->addChild(childNode2);
        std::shared_ptr<simple2dengine::Node> childNode3 = std::make_shared<simple2dengine::Node>(engine);
        std::shared_ptr<simple2dengine::Node> childNode4 = std::make_shared<simple2dengine::Node>(engine);
        childNode1->addChild(childNode3);
        childNode1->addChild(childNode4);

        REQUIRE(scenemanager.getSceneCount() == 2);

        scenemanager.switchToScene("menu");
        scenemanager.removeScene("root");

        REQUIRE(scenemanager.getSceneCount() == 1);

        scenemanager.removeScene("menu");

        REQUIRE(scenemanager.getSceneCount() == 0);
    }
}
