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
         * @brief Construct a new Text Node with a font applied.
         *
         * @param engineRef reference to Engine object.
         * @param nodeName name of the node.
         * @param filename Name of font file with relative or full path.
         *
         * @see Engine.
         * @see Node.
         * @see sf::Text.
         */
        TextNode(Engine& engineRef, const std::string& nodeName, const std::string& filename);
        /**
         * @brief Set font source of Text Node.
         *
         * @param filename Name of file with relative or full path.
         * @param isAssetLoaded If true - we assume that file is already loaded in asset manager, if false - asset manager will load it before using.
         *
         * @see AssetManager.
         */
        void setFont(const std::string& filename, bool isAssetLoaded = true);
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

        using CanvasNode::setPosition;
        using CanvasNode::getPosition;
        using CanvasNode::move;

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
