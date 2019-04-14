#include "GameScene.h"
#include "simple2dengine/configuration.h"
#include "simple2dengine/engine.h"
#include "simple2dengine/managers/input_manager.h"
#include "simple2dengine/nodes/node.h"

int main()
{
    simple2dengine::Configuration config;
    config.fps = 60;
    config.window.width = 800;
    config.window.height = 800;
    config.window.name = std::string("Simple Demo");

    simple2dengine::Engine engine(config);

    // engine.getInputManager().registerAction("reset", sf::Keyboard::Key::Space);

    engine.getSceneManager().addScene(std::make_shared<GameScene>("game"));
    engine.getSceneManager().activateScene("game");

    engine.run();

    return 0;
}
