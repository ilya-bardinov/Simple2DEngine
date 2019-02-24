#include "simple2dengine/nodes/text_node.h"
#include "simple2dengine/managers/asset_manager.h"

namespace simple2dengine
{
    void TextNode::setFont(const std::string& filename, bool isAssetLoaded/* = true*/)
    {
        if(!isAssetLoaded)
        {
            engine.getAssetManager().load(filename);
        }
        sf::Font* font = engine.getAssetManager().getAsset<sf::Font>(filename);
        if(font == nullptr)
        {
            std::cout << "TextNode::setFont - error when loading file " << filename << std::endl;
            return;
        }
        text.setFont(*font);
    }

    void TextNode::setText(const std::string& textString)
    {
        text.setString(textString);
    }

    void TextNode::setSize(unsigned int size)
    {
        text.setCharacterSize(size);
    }

    void TextNode::setFillColor(const sf::Color& color)
    {
        text.setFillColor(color);
    }

    void TextNode::setPosition(const sf::Vector2f& _position)
    {
        Node::setPosition(_position);

        text.setPosition(getAbsolutePosition());
    }

    void TextNode::render()
    {
        Node::render();

        if(isAbsoluteVisible())
        {
            engine.getRenderWindow().draw(text);
        }
    }
}
