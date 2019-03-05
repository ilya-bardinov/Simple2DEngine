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
    class SpriteNode : public CanvasNode
    {
      public:
        /**
         * @brief Construct a new Sprite Node.
         *
         * @param engineRef reference to Engine object.
         * @param nodeName name of the node.
         *
         * @see Engine.
         * @see Node.
         */
        SpriteNode(Engine& engineRef, const std::string& nodeName) : CanvasNode(engineRef, nodeName) { };
        /**
         * @brief Set image source to Node.
         *
         * @param filename Name of file with relative or full path.
         * @param isAssetLoaded If true - we assume that file is already loaded in asset manager, if false - asset manager will load it before using.
         *
         * @see AssetManager.
         */
        void setImage(const std::string& filename, bool isAssetLoaded = true);
        /**
         * @brief Update transform of the sprite to correctly display it.
         *
         */
        virtual void updateTransform() override;

      protected:
        /**
         * @brief Override base render().
         * We need to draw an image.
         *
         * @see Node.
         */
        virtual void render() override;

      private:
        sf::Sprite sprite;
    };
} // namespace simple2dengine

#endif // _SIMPLE2DENGINE_NODES_CANVAS_SPRITE_NODE_H_
