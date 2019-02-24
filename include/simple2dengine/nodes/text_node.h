/**
 * @file text_node.h
 * @author Ilya Bardinov (ilya.bardinov@gmail.com)
 * @brief text node
 * @version 0.1
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
    /**
     * @brief Text node.
    *
    */
    class TextNode : public Node
    {
      public:
        TextNode(Engine& engineRef) : Node(engineRef) { };

        void setFont(const std::string& filename, bool isAssetLoaded = true);
        void setText(const std::string& textString);
        void setSize(unsigned int size);
        void setFillColor(const sf::Color& color);

        virtual void setPosition(const sf::Vector2f& position) override;

      protected:
        virtual void render() override;

      private:
        sf::Text text;
    };
} // namespace simple2dengine

#endif // _SIMPLE2DENGINE_NODES_TEXT_NODE_H_
