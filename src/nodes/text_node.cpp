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
            std::cout << "TextNode::setFont - error in node '" << getName() << "' when loading file '" << filename << "'" << std::endl;
            return;
        }
        text.setFont(*font);
        // we need to update anchor due to possible text size change
        updatePosition();
    }

    void TextNode::setText(const std::string& textString)
    {
        text.setString(textString);
        // we need to update anchor due to possible text size change
        updatePosition();
    }

    void TextNode::setCharacterSize(unsigned int size)
    {
        text.setCharacterSize(size);
        // we need to update anchor due to possible text size change
        updatePosition();
    }

    void TextNode::setFillColor(const Color& color)
    {
        text.setFillColor(color);
    }

    Vector2f TextNode::getSize() const
    {
        return Vector2f(
            text.getLocalBounds().width * text.getScale().x,
            text.getLocalBounds().height * text.getScale().y);
    }

    void TextNode::render()
    {
        Node::render();

        if(isAbsoluteVisible())
        {
            engine.getRenderWindow().draw(text);
        }
    }

    void TextNode::updatePosition()
    {
        Node::updatePosition();

        Anchor textAnchor = getAnchor();
        Vector2f anchorPosition(0.0f, 0.0f);
        if((textAnchor & Anchor::Center) == Anchor::Center)
        {
            anchorPosition.x = text.getLocalBounds().width  / 2.0f;
            anchorPosition.y = text.getLocalBounds().height / 1.4f;
        }
        if((textAnchor & Anchor::Left) == Anchor::Left)
        {
            anchorPosition.x = 0.0f;
        }
        if((textAnchor & Anchor::Top) == Anchor::Top)
        {
            anchorPosition.y = 0.0f;
        }
        if((textAnchor & Anchor::Bottom) == Anchor::Bottom)
        {
            anchorPosition.y = text.getLocalBounds().height;
        }
        if((textAnchor & Anchor::Right) == Anchor::Right)
        {
            anchorPosition.x = text.getLocalBounds().width ;
        }

        text.setOrigin(anchorPosition);
        text.setPosition(getAbsolutePosition());
    }
}
