// Let Catch provide main():
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "Simple2DEngine/Engine.hpp"

TEST_CASE("State of window in Engine") {

    Simple2DEngine::Engine engine;
    REQUIRE(engine.isWindowOpen() == false);

    SECTION("Engine is initialized") {
        engine.openWindow(100, 100, "test");

        REQUIRE(engine.isWindowOpen() == true);
    }
    SECTION("Engine is not initialized") {
        engine.closeWindow();

        REQUIRE(engine.isWindowOpen() == false);
    }
    SECTION("Engine is initialized and then close the window") {
        engine.openWindow(100, 100, "test");
        
        REQUIRE(engine.isWindowOpen() == true);

        engine.closeWindow();

        REQUIRE(engine.isWindowOpen() == false);
    }
}