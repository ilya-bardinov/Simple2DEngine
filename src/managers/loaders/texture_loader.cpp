#include <iostream>
#include <algorithm>

#include "simple2dengine/managers/loaders/texture_loader.h"

namespace simple2dengine
{
    void TextureLoader::load(const std::string& filename)
    {
        auto position = textures.find(filename);
        if (position != textures.end())
        {
            std::cout << "TextureLoader::load - file '" << filename << "' already loaded!" << std::endl;
            return;
        }

        sf::Texture texture;
        if (!texture.loadFromFile(filename))
        {
            std::cout << "TextureLoader::load - error when loading file '" << filename << "'!" << std::endl;
            return;
        }

        textures[filename] = texture;
    }

    void TextureLoader::unload(const std::string& filename)
    {
        auto position = textures.find(filename);
        if (position != textures.end())
        {
            textures.erase(position);
        }
        else
        {
            std::cout << "TextureLoader::unload - file '" << filename << "' is not loaded!" << std::endl;
        }
    }

    std::shared_ptr<Asset> TextureLoader::getAsset(const std::string& filename) const
    {
        auto position = textures.find(filename);
        if (position != textures.end())
        {
            auto asset = std::make_shared<Asset>();
            asset->nativeAsset = (void *)&position->second;
            return asset;
        }
        else
        {
            std::cout << "TextureLoader::getAsset - file '" << filename << "' is not loaded!" << std::endl;
        }
        return nullptr;
    }
}
