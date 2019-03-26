/**
 * @file GameScene.h
 * @author Ilya Bardinov (ilya.bardinov@gmail.com)
 * @brief
 * @date 2019-03-26
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef _SIMPLE_DEMO_GAME_SCENE_H_
#define _SIMPLE_DEMO_GAME_SCENE_H_

#include "simple2dengine/nodes/node.h"
#include "simple2dengine/nodes/canvas/text_node.h"
#include "simple2dengine/engine.h"

#include "GridNode.h"

using namespace simple2dengine;

class GameScene : public simple2dengine::Node
{
    public:
        using Node::Node;
        virtual ~GameScene() { };

        virtual void onCreate() override;
        virtual void onInput(sf::Event event) override;
        virtual void onUpdate(int deltaInMs) override;
        virtual void onDestroy() override;

    private:
        std::shared_ptr<GridNode> gridNode;
        std::shared_ptr<simple2dengine::TextNode> fpsText;

        uint16_t fpsUpdateTimer = 0;

        const uint8_t gridRows = 3;
        const uint8_t gridColumns = 3;
        const float gridMargin = 20.0f;
        const uint16_t fpsTimer = 1000;
};

#endif // _SIMPLE_DEMO_GAME_SCENE_H_
