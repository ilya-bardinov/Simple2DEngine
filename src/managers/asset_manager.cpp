#include "simple2dengine/managers/asset_manager.h"

namespace simple2dengine
{
    sf::Texture AssetManager::loadTexture(const std::string& filename)
    {
        auto it = textures.find(filename);

        if (it != textures.end())
            return it->second;

        sf::Texture texture;
        if (!texture.loadFromFile("image.png"))
        {
            std::cout << "AssetManager::loadTexture - error when loading file " << filename << std::endl;
            return texture;
        }

        textures[filename] = texture;
        return texture;
    }

    void AssetManager::unloadTexture(const std::string& filename)
    {
        auto it = textures.find(filename);

        if (it != textures.end())
        {
            sf::Texture texture = it->second;
            textures.erase(it);
        }
    }

    void AssetManager::unloadTextures()
    {
        textures.clear();
    }
}
