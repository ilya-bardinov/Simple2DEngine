#include "simple2dengine/nodes/sprite.h"

namespace simple2dengine
{
    void SpriteNode::setImage(const std::string& filename)
    {
        sf::Texture texture = engine.getAssetManager().loadTexture(filename);
        sprite.setTexture(texture);
    }

    void SpriteNode::setPosition(float x, float y)
    {
        sprite.setPosition(sf::Vector2f(x, y));
    }
}
