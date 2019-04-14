#include "simple2dengine/nodes/canvas/text_node.h"
#include "simple2dengine/managers/asset_manager.h"

namespace simple2dengine
{
    void TextNode::setFont(const AssetManager& assetManager, const std::string& filename)
    {
        const sf::Font* font = assetManager.getAsset<sf::Font>(filename);
        if(font == nullptr)
        {
            std::cout << "TextNode::setFont - error in node '" << getName() << "' when loading file '"
                      << filename << "'" << std::endl;
            return;
        }
        Text::setFont(*font);
        // we need to update anchor due to possible text size change
        updateTransform();
    }

    void TextNode::setString(const std::string& textString)
    {
        Text::setString(textString);
        // we need to update anchor due to possible text size change
        updateTransform();
    }

    void TextNode::setCharacterSize(unsigned int size)
    {
        Text::setCharacterSize(size);
        // we need to update anchor due to possible text size change
        updateTransform();
    }

    void TextNode::render()
    {
        if(isVisibleInTree())
        {
            engine->getRenderWindow().draw(*this);
        }

        CanvasNode::render();
    }

    void TextNode::updateTransform()
    {
        const Anchor textAnchor = getAnchor();
        sf::Vector2f anchorPosition(0.0f, 0.0f);
        if((textAnchor & Anchor::Center) == Anchor::Center)
        {
            anchorPosition.x = getLocalBounds().width / 2.0f;
            anchorPosition.y = getLocalBounds().height / 2.0f;
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
            anchorPosition.y = getLocalBounds().height;
        }
        if((textAnchor & Anchor::Right) == Anchor::Right)
        {
            anchorPosition.x = getLocalBounds().width;
        }

        setOrigin(anchorPosition);
        Text::setPosition(getGlobalPosition());

        CanvasNode::updateTransform();
    }
} // namespace simple2dengine
