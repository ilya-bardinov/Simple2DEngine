#include <iostream>

#include "simple2dengine/managers/loaders/font_loader.h"

namespace simple2dengine
{
    void FontLoader::load(const std::string& filename)
    {
        auto position = fonts.find(filename);
        if (position != fonts.end())
        {
            std::cout << "FontLoader::load - file '" << filename << "' already loaded!" << std::endl;
            return;
        }

        sf::Font font;
        if (!font.loadFromFile(filename))
        {
            std::cout << "FontLoader::load - error when loading file '" << filename << "'!" << std::endl;
            return;
        }

        fonts[filename] = font;
    }

    void FontLoader::unload(const std::string& filename)
    {
        auto position = fonts.find(filename);
        if (position != fonts.end())
        {
            fonts.erase(position);
        }
        else
        {
            std::cout << "FontLoader::unload - file '" << filename << "' is not loaded!" << std::endl;
        }
    }

    std::shared_ptr<Asset> FontLoader::getAsset(const std::string& filename) const
    {
        auto position = fonts.find(filename);
        if (position != fonts.end())
        {
            auto asset = std::make_shared<Asset>();
            asset->nativeAsset = (void *)&position->second;
            return asset;
        }
        else
        {
            std::cout << "FontLoader::getAsset - file '" << filename << "' is not loaded!" << std::endl;
        }
        return nullptr;
    }
}
