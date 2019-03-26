#include "simple2dengine/nodes/canvas/sprite_node.h"
#include "simple2dengine/managers/asset_manager.h"

namespace simple2dengine
{
    SpriteNode::SpriteNode(Engine& engineRef, const std::string& nodeName, const std::string& filename)
    : CanvasNode(engineRef, nodeName)
    {
        setImage(filename);
    }

    void SpriteNode::setImage(const std::string& filename, bool isAssetLoaded/* = true*/)
    {
        if(!isAssetLoaded)
        {
            engine.getAssetManager().load(filename);
        }
        const sf::Texture* texture = engine.getAssetManager().getAsset<sf::Texture>(filename);
        if(texture == nullptr)
        {
            std::cout << "SpriteNode::setImage - error in node '" << getName() << "' when loading file '" << filename << "'" << std::endl;
            return;
        }

        setTexture(*texture, true);
        // we need to update anchor due to possible sprite size change
        updateTransform();
    }

    void SpriteNode::render()
    {
        if(isVisibleInTree())
        {
            engine.getRenderWindow().draw(*this);
        }

        CanvasNode::render();
    }

    void SpriteNode::updateTransform()
    {
        const Anchor spriteAnchor = getAnchor();
        sf::Vector2f anchorPosition(0.0f, 0.0f);
        if((spriteAnchor & Anchor::Center) == Anchor::Center)
        {
            anchorPosition.x = getLocalBounds().width / 2.0f;
            anchorPosition.y = getLocalBounds().height / 2.0f;
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
            anchorPosition.y = getLocalBounds().height;
        }
        if((spriteAnchor & Anchor::Right) == Anchor::Right)
        {
            anchorPosition.x = getLocalBounds().width;
        }

        setOrigin(anchorPosition);
        Sprite::setPosition(getGlobalPosition());

        CanvasNode::updateTransform();
    }
}
