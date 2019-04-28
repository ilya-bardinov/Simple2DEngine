// Let Catch provide main():
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "simple2dengine/configuration.h"
#include "simple2dengine/engine.h"

TEST_CASE("Test Engine")
{
    simple2dengine::Configuration config;
    config.framerate.verticalSync = true;
    config.window.width = 400;
    config.window.height = 300;
    config.window.name = std::string("Unit Test");
    simple2dengine::Engine engine(config);
    engine.stop();
}
