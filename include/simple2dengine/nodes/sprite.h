/**
 * @file sprite.h
 * @author Ilya Bardinov (ilya.bardinov@gmail.com)
 * @brief sprite node
 * @version 0.1
 * @date 2019-02-19
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef SIMPLE2DENGINE_NODES_SPRITE_H_
#define SIMPLE2DENGINE_NODES_SPRITE_H_

#include <string>

#include "SFML/Graphics/Sprite.hpp"

#include "simple2dengine/engine.h"
#include "simple2dengine/nodes/node.h"
#include "simple2dengine/managers/asset_manager.h"

namespace simple2dengine
{
    /**
     * @brief Sprite node.
    *
    */
    class SpriteNode : public Node
    {
      using Node::Node;
      public:
        SpriteNode(Engine& engine) : Node(engine) {  };
        /**
         * @brief add Image to SpriteNode object.
         *
         * @param filename Name of file with relative or full path
         */
        void setImage(const std::string& filename);
        /**
         * @brief Set the Position of Sprite.
         *
         * @param x X coordinate of the new position
         * @param y Y coordinate of the new position
         */
        void setPosition(float x, float y);

      private:
        sf::Sprite sprite;
    };
} // namespace simple2dengine

#endif // SIMPLE2DENGINE_NODES_SPRITE_H_
