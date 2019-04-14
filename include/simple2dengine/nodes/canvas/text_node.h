/**
 * @file text_node.h
 * @author Ilya Bardinov (ilya.bardinov@gmail.com)
 * @brief Text Node
 * @date 2019-02-24
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef _SIMPLE2DENGINE_NODES_CANVAS_TEXT_NODE_H_
#define _SIMPLE2DENGINE_NODES_CANVAS_TEXT_NODE_H_

#include <string>

#include "SFML/Graphics/Text.hpp"

#include "simple2dengine/engine.h"
#include "simple2dengine/nodes/canvas/canvas_node.h"

namespace simple2dengine
{
    /**
     * @brief Text node.
     * Used to draw text strings.
     *
     */
    class TextNode : public CanvasNode, public sf::Text
    {
      public:
        using CanvasNode::CanvasNode;
        /**
         * @brief Set or load font.
         *
         * @param assetManager Asset Manager where asset should be stored.
         * @param filename Name of file with relative or full path.
         *
         * @see AssetManager.
         */
        void setFont(const AssetManager& assetManager, const std::string& filename);
        /**
         * @brief Set text string.
         *
         * @param textString - text to display.
         */
        void setString(const std::string& textString);
        /**
         * @brief Set size.
         *
         * @param size of text.
         */
        void setCharacterSize(unsigned int size);
        /**
         * @brief Update transform of the text to correctly display it.
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

#endif // _SIMPLE2DENGINE_NODES_CANVAS_TEXT_NODE_H_
