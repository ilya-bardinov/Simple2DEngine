// Let Catch provide main():
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "simple2dengine/engine.h"
#include "simple2dengine/scenes/node.h"

TEST_CASE("State of window in Engine") {

    simple2dengine::Engine engine;
    REQUIRE(engine.isWindowOpen() == false);

    SECTION("Engine is initialized") {
        engine.openWindow(100, 100, "test");

        REQUIRE(engine.isWindowOpen() == true);

        engine.update();
    }
    SECTION("Engine is not initialized") {
        engine.closeWindow();
        engine.update();
        
        REQUIRE(engine.isWindowOpen() == false);
    }
    SECTION("Engine is initialized and then close the window") {
        engine.openWindow(100, 100, "test");
        
        REQUIRE(engine.isWindowOpen() == true);

        engine.closeWindow();

        REQUIRE(engine.isWindowOpen() == false);
    }
}

TEST_CASE("State of scenes in Engine") {
    simple2dengine::Engine engine;
    engine.openWindow(100, 100, "test");
    std::shared_ptr<simple2dengine::Node> node = std::make_shared<simple2dengine::Node>();
    engine.startWithScene(node);

    SECTION("Push and Pop scene") {
        REQUIRE(node->getSceneManager()->getScenesCount() == 1);
        node->getSceneManager()->popScene();
        engine.update();
        REQUIRE(node->getSceneManager()->getScenesCount() == 0);
        node->getSceneManager()->pushScene(node);
        engine.update();
        REQUIRE(node->getSceneManager()->getScenesCount() == 1);
        node->getSceneManager()->popScene();
        REQUIRE(node->getSceneManager()->getScenesCount() == 0);
    }

    SECTION("Replace scene") {
        REQUIRE(node->getSceneManager()->getScenesCount() == 1);
        std::shared_ptr<simple2dengine::Node> node2 = std::make_shared<simple2dengine::Node>();
        node->getSceneManager()->replaceScene(node2);
        REQUIRE(node->getSceneManager()->getScenesCount() == 1);
    }
}