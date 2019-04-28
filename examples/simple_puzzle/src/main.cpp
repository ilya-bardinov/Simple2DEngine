#include "GameScene.h"
#include "simple2dengine/configuration.h"
#include "simple2dengine/engine.h"
#include "simple2dengine/managers/input_manager.h"
#include "simple2dengine/nodes/node.h"

int main()
{
    simple2dengine::Configuration config;
    config.framerate.verticalSync = true;
    config.window.width = 800;
    config.window.height = 800;
    config.window.name = std::string("Simple Puzzle");
    config.window.style = sf::Style::Default;
    config.window.position = sf::Vector2i(600, 300);

    simple2dengine::Engine engine(config);
    engine.setBackgroundColor(sf::Color::White);

    // engine.getInputManager().registerAction("reset", sf::Keyboard::Key::Space);

    engine.getSceneManager().addScene(std::make_shared<GameScene>("game"));
    engine.getSceneManager().activateScene("game");

    engine.run();

    return 0;
}
