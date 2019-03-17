#include "GameScene.h"
#include "simple2dengine/configuration.h"
#include "simple2dengine/engine.h"
#include "simple2dengine/nodes/node.h"
#include "simple2dengine/managers/input_manager.h"

int main (int argc, char *argv[]) 
{
    simple2dengine::Configuration config;
    config.fps = 60;
    config.window.width = 1000;
    config.window.height = 800;
    config.window.name = std::string("Unit Test");
    simple2dengine::Engine engine(config);

    engine.getInputManager().registerAction("ui_left", sf::Keyboard::Key::A);
    engine.getInputManager().registerAction("ui_right", sf::Keyboard::Key::D);
    engine.getInputManager().registerAction("ui_up", sf::Keyboard::Key::W);
    engine.getInputManager().registerAction("ui_down", sf::Keyboard::Key::S);
    engine.getInputManager().registerAction("ui_button", sf::Mouse::Button::Left);
    engine.getInputManager().registerAction("ui_button", sf::Mouse::Button::Right);

    auto node = std::make_shared<GameScene>(engine, "game");
    engine.getSceneManager().addScene(std::move(node));
    engine.getSceneManager().activateScene("game");

    engine.run();
    

    return 0;
}