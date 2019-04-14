/**
 * @file sprite_node.h
 * @author Ilya Bardinov (ilya.bardinov@gmail.com)
 * @brief Sprite Node
 * @date 2019-02-19
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef _SIMPLE2DENGINE_NODES_CANVAS_SPRITE_NODE_H_
#define _SIMPLE2DENGINE_NODES_CANVAS_SPRITE_NODE_H_

#include <string>

#include "SFML/Graphics/Sprite.hpp"

#include "simple2dengine/engine.h"
#include "simple2dengine/nodes/canvas/canvas_node.h"

namespace simple2dengine
{
    /**
     * @brief Sprite node.
     * Used to draw different images.
     *
     */
    class SpriteNode : public CanvasNode, public sf::Sprite
    {
      public:
        using CanvasNode::CanvasNode;
        /**
         * @brief Set or load image/texture.
         *
         * @param assetManager Asset Manager where asset should be stored.
         * @param filename Name of file with relative or full path.
         *
         * @see AssetManager.
         */
        void setImage(const AssetManager& assetManager, const std::string& filename);
        /**
         * @brief Update transform of the sprite to correctly display it.
         *
         */
        virtual void updateTransform() override;

        using CanvasNode::getPosition;
        using CanvasNode::move;
        using CanvasNode::setPosition;

      protected:
        /**
         * @brief Override base render().
         * We need to draw an image.
         *
         * @see Node.
         */
        virtual void render() override;
    };
} // namespace simple2dengine

#endif // _SIMPLE2DENGINE_NODES_CANVAS_SPRITE_NODE_H_
