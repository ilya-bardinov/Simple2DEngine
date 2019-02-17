// Let Catch provide main():
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "simple2dengine/engine.h"
#include "simple2dengine/scenes/node.h"

TEST_CASE("State of window in Engine") {

    simple2dengine::Engine engine;

    REQUIRE(engine.isWindowOpen() == false);

    SECTION("Open window and update") {
        engine.openWindow(100, 100, "test");

        REQUIRE(engine.isWindowOpen() == true);

        engine.update();
    }
    SECTION("Close window and update") {
        engine.closeWindow();
        engine.update();
        
        REQUIRE(engine.isWindowOpen() == false);
    }
    SECTION("Open and close window") {
        engine.openWindow(100, 100, "test");
        
        REQUIRE(engine.isWindowOpen() == true);

        engine.closeWindow();

        REQUIRE(engine.isWindowOpen() == false);
    }
    SECTION("Open window twice and close it ") {
        engine.openWindow(100, 100, "test");

        REQUIRE(engine.isWindowOpen() == true);

        engine.openWindow(100, 100, "test");
        
        REQUIRE(engine.isWindowOpen() == true);

        engine.closeWindow();

        REQUIRE(engine.isWindowOpen() == false);
    }
}

TEST_CASE("State of scenes in Engine") {
    simple2dengine::Engine engine;

    std::shared_ptr<simple2dengine::Node> node = std::make_shared<simple2dengine::Node>();

    engine.startWithScene(node);

    REQUIRE(node->getSceneManager()->getScenesCount() == 1);

    SECTION("Pop, push and pop the same scene") {
        node->getSceneManager()->popScene();
        REQUIRE(node->getSceneManager()->getScenesCount() == 0);

        node->getSceneManager()->pushScene(node);
        REQUIRE(node->getSceneManager()->getScenesCount() == 1);

        node->getSceneManager()->popScene();
        REQUIRE(node->getSceneManager()->getScenesCount() == 0);
    }
    SECTION("Replace scene with another one") {
        std::shared_ptr<simple2dengine::Node> node2 = std::make_shared<simple2dengine::Node>();
        node->getSceneManager()->replaceScene(node2);

        REQUIRE(node->getSceneManager()->getScenesCount() == 1);
    }
    SECTION("Call startWithScene twice") {
        std::shared_ptr<simple2dengine::Node> node2 = std::make_shared<simple2dengine::Node>();
        engine.startWithScene(node2);

        REQUIRE(node->getSceneManager()->getScenesCount() == 1);
    }
    SECTION("Update engine and set framerate") {
        engine.update();
        engine.setFramerateLimit(60);
        engine.update();
    }
}