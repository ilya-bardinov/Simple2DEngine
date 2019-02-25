/**
 * @file text_node.h
 * @author Ilya Bardinov (ilya.bardinov@gmail.com)
 * @brief Text Node
 * @date 2019-02-24
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef _SIMPLE2DENGINE_NODES_TEXT_NODE_H_
#define _SIMPLE2DENGINE_NODES_TEXT_NODE_H_

#include <string>

#include "SFML/Graphics/Text.hpp"

#include "simple2dengine/engine.h"
#include "simple2dengine/nodes/node.h"

namespace simple2dengine
{
    typedef sf::Color Color;
    /**
     * @brief Text node.
     * Used to draw text strings.
     *
     */
    class TextNode : public Node
    {
      public:
        /**
         * @brief Construct a new Text Node.
         *
         * @param engineRef reference to Engine object.
         * @param nodeName name of the node.
         *
         * @see Engine.
         * @see Node.
         */
        TextNode(Engine& engineRef, const std::string& nodeName) : Node(engineRef, nodeName) { };
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
        void setText(const std::string& textString);
        /**
         * @brief Set size.
         *
         * @param size of text.
         */
        void setCharacterSize(unsigned int size);
        /**
         * @brief Set color.
         *
         * @param color RGBA color of text.
         *
         * @see Color.
         */
        void setFillColor(const Color& color);
        /**
         * @brief Set position of Text Node.
         *
         * @param position relative to parent.
         *
         * @see Node.
         */
        virtual void setPosition(const Vector2f& position) override;

      protected:
        /**
         * @brief Override base render().
         * We need to draw an image.
         *
         * @see Node.
         */
        virtual void render() override;

      private:
        sf::Text text;
    };
} // namespace simple2dengine

#endif // _SIMPLE2DENGINE_NODES_TEXT_NODE_H_
