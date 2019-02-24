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
            std::cout << "SpriteNode::setImage - error when loading file " << filename << std::endl;
            return;
        }
        sprite.setTexture(*texture);
    }

    void SpriteNode::setPosition(const Vector2f& _position)
    {
        Node::setPosition(_position);

        sprite.setPosition(getAbsolutePosition());
    }

    void SpriteNode::render()
    {
        Node::render();

        if(isAbsoluteVisible())
        {
            engine.getRenderWindow().draw(sprite);
        }
    }
}
