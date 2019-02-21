#include "simple2dengine/nodes/sprite.h"
#include "simple2dengine/managers/asset_manager.h"

namespace simple2dengine
{
    void SpriteNode::setImage(const std::string& filename)
    {
        engine.getAssetManager().load(filename);
        sf::Texture* texture = engine.getAssetManager().getAsset<sf::Texture>(filename);
        if(texture == nullptr)
        {
            std::cout << "SpriteNode::setImage - error when loading file " << filename << std::endl;
            return;
        }
        sprite.setTexture(*texture);
    }

    void SpriteNode::setPosition(float x, float y)
    {
        sprite.setPosition(sf::Vector2f(x, y));
    }

    const sf::Vector2f& SpriteNode::getPosition() const
    {
        return sprite.getPosition();
    }

    void SpriteNode::moveTo(float x, float y)
    {
        sprite.move(sf::Vector2f(x, y));
    }

    void SpriteNode::render()
    {
        engine.getRenderWindow().draw(sprite);
        Node::render();
    }
}
