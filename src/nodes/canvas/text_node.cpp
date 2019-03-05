#include "simple2dengine/nodes/canvas/text_node.h"
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
        updateTransform();
    }

    void TextNode::setText(const std::string& textString)
    {
        text.setString(textString);
        // we need to update anchor due to possible text size change
        updateTransform();
    }

    void TextNode::setCharacterSize(unsigned int size)
    {
        text.setCharacterSize(size);
        // we need to update anchor due to possible text size change
        updateTransform();
    }

    void TextNode::setFillColor(const sf::Color& color)
    {
        text.setFillColor(color);
    }

    void TextNode::render()
    {
        if(isVisibleInTree())
        {
            engine.getRenderWindow().draw(text);
        }

        CanvasNode::render();
    }

    void TextNode::updateTransform()
    {
        Anchor textAnchor = getAnchor();
        Vector2f anchorPosition(0.0f, 0.0f);
        if((textAnchor & Anchor::Center) == Anchor::Center)
        {
            anchorPosition.x = text.getLocalBounds().width  / 2.0f;
            anchorPosition.y = text.getLocalBounds().height / 2.0f;
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
        text.setPosition(getGlobalPosition());

        CanvasNode::updateTransform();
    }
}
