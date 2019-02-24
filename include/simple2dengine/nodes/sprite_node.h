/**
 * @file sprite_node.h
 * @author Ilya Bardinov (ilya.bardinov@gmail.com)
 * @brief sprite node
 * @version 0.1
 * @date 2019-02-19
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef _SIMPLE2DENGINE_NODES_SPRITE_NODE_H_
#define _SIMPLE2DENGINE_NODES_SPRITE_NODE_H_

#include <string>

#include "SFML/Graphics/Sprite.hpp"

#include "simple2dengine/engine.h"
#include "simple2dengine/nodes/node.h"

namespace simple2dengine
{
    /**
     * @brief Sprite node.
    *
    */
    class SpriteNode : public Node
    {
      public:
        SpriteNode(Engine& engineRef) : Node(engineRef) { };
        /**
         * @brief add Image to SpriteNode object.
         *
         * @param filename Name of file with relative or full path
         */
        void setImage(const std::string& filename, bool isAssetLoaded = true);

        virtual void setPosition(const sf::Vector2f& position) final;

      protected:
        virtual void render() override;

      private:
        sf::Sprite sprite;
    };
} // namespace simple2dengine

#endif // _SIMPLE2DENGINE_NODES_SPRITE_NODE_H_
