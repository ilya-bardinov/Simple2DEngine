/**
 * @file texture_loader.h
 * @author Ilya Bardinov (ilya.bardinov@gmail.com)
 * @brief
 * @version 0.1
 * @date 2019-02-21
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef _SIMPLE2DENGINE_MANAGERS_LOADERS_TEXTURE_LOADER_H_
#define _SIMPLE2DENGINE_MANAGERS_LOADERS_TEXTURE_LOADER_H_

#include <string>
#include <unordered_map>

#include "simple2dengine/managers/loaders/loader.h"

#include "SFML/Graphics/Texture.hpp"

namespace simple2dengine
{
    class TextureLoader : public Loader
    {
      public:
        virtual void load(const std::string& filename) final;
        virtual void unload(const std::string& filename) final;
        virtual std::shared_ptr<Asset> getAsset(const std::string& filename) const final;

      private:
        std::unordered_map<std::string, sf::Texture> textures;
    };
} // simple2dengine

#endif // _SIMPLE2DENGINE_MANAGERS_LOADERS_TEXTURE_LOADER_H_
