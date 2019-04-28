#include <iostream>

#include "simple2dengine/managers/loaders/texture_loader.h"

namespace simple2dengine
{
    void TextureLoader::load(const std::string& filename)
    {
        const auto position = textures.find(filename);
        if(position != textures.end())
        {
            std::cout << "TextureLoader::load - file '" << filename << "' already loaded!" << std::endl;
            return;
        }

        sf::Texture texture;
        if(!texture.loadFromFile(filename))
        {
            std::cout << "TextureLoader::load - error when loading file '" << filename << "'!" << std::endl;
            return;
        }

        textures[filename] = texture;
    }

    void TextureLoader::unload(const std::string& filename)
    {
        const auto position = textures.find(filename);
        if(position != textures.end())
        {
            textures.erase(position);
        }
        else
        {
            std::cout << "TextureLoader::unload - file '" << filename << "' is not loaded!" << std::endl;
        }
    }

    const BaseAsset* TextureLoader::getAsset(const std::string& filename) const
    {
        const auto position = textures.find(filename);
        if(position != textures.end())
        {
            Asset<sf::Texture>* loadedAsset = new Asset<sf::Texture>();
            loadedAsset->asset = &(position->second);
            return loadedAsset;
        }
        else
        {
            std::cout << "TextureLoader::getAsset - file '" << filename << "' is not loaded!" << std::endl;
        }
        return nullptr;
    }
} // namespace simple2dengine
