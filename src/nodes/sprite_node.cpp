#include "simple2dengine/nodes/sprite_node.h"
#include "simple2dengine/managers/asset_manager.h"

namespace simple2dengine
{
    void SpriteNode::setImage(const std::string& filename, bool isAssetLoaded/* = true*/)
    {
        if(!isAssetLoaded)
        {
            engine.getAssetManager().load(filename);
        }
        sf::Texture* texture = engine.getAssetManager().getAsset<sf::Texture>(filename);
        if(texture == nullptr)
        {
            std::cout << "SpriteNode::setImage - error in node '" << getName() << "' when loading file '" << filename << "'" << std::endl;
            return;
        }

        sprite.setTexture(*texture);
        // we need to update anchor due to possible sprite size change
        updatePosition();
    }

    Vector2f SpriteNode::getSize() const
    {
        return Vector2f(
            sprite.getTexture()->getSize().x * sprite.getScale().x,
            sprite.getTexture()->getSize().y * sprite.getScale().y);
    }

    void SpriteNode::render()
    {
        Node::render();

        if(isAbsoluteVisible())
        {
            engine.getRenderWindow().draw(sprite);
        }
    }

    void SpriteNode::updatePosition()
    {
        Node::updatePosition();

        Anchor spriteAnchor = getAnchor();
        Vector2f anchorPosition(0.0f, 0.0f);
        if((spriteAnchor & Anchor::Center) == Anchor::Center)
        {
            anchorPosition.x = sprite.getLocalBounds().width / 2.0f;
            anchorPosition.y = sprite.getLocalBounds().height / 2.0f;
        }
        if((spriteAnchor & Anchor::Left) == Anchor::Left)
        {
            anchorPosition.x = 0.0f;
        }
        if((spriteAnchor & Anchor::Top) == Anchor::Top)
        {
            anchorPosition.y = 0.0f;
        }
        if((spriteAnchor & Anchor::Bottom) == Anchor::Bottom)
        {
            anchorPosition.y = sprite.getLocalBounds().height;
        }
        if((spriteAnchor & Anchor::Right) == Anchor::Right)
        {
            anchorPosition.x = sprite.getLocalBounds().width;
        }

        sprite.setOrigin(anchorPosition);
        sprite.setPosition(getAbsolutePosition());
    }
}
