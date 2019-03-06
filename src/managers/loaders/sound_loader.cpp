#include <iostream>

#include "simple2dengine/managers/loaders/sound_loader.h"

namespace simple2dengine
{
    void SoundLoader::load(const std::string& filename)
    {
        auto position = buffers.find(filename);
        if (position != buffers.end())
        {
            std::cout << "SoundLoader::load - file '" << filename << "' already loaded!" << std::endl;
            return;
        }

        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile(filename))
        {
            std::cout << "SoundLoader::load - error when loading file '" << filename << "'!" << std::endl;
            return;
        }

        buffers[filename] = buffer;
    }

    void SoundLoader::unload(const std::string& filename)
    {
        auto position = buffers.find(filename);
        if (position != buffers.end())
        {
            buffers.erase(position);
        }
        else
        {
            std::cout << "SoundLoader::unload - file '" << filename << "' is not loaded!" << std::endl;
        }
    }

    BaseAsset* SoundLoader::getAsset(const std::string& filename) const
    {
        auto position = buffers.find(filename);
        if (position != buffers.end())
        {
            Asset<sf::SoundBuffer>* loadedAsset = new Asset<sf::SoundBuffer>();
            loadedAsset->asset = &(position->second);
            return loadedAsset;
        }
        else
        {
            std::cout << "SoundLoader::getAsset - file '" << filename << "' is not loaded!" << std::endl;
        }
        return nullptr;
    }
}
