/**
 * @file font_loader.h
 * @author Ilya Bardinov (ilya.bardinov@gmail.com)
 * @brief
 * @version 0.1
 * @date 2019-02-23
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef _SIMPLE2DENGINE_MANAGERS_LOADERS_FONT_LOADER_H_
#define _SIMPLE2DENGINE_MANAGERS_LOADERS_FONT_LOADER_H_

#include <string>
#include <unordered_map>
#include <memory>

#include "simple2dengine/managers/loaders/loader.h"

#include "SFML/Graphics/Font.hpp"

namespace simple2dengine
{
    class FontLoader : public Loader
    {
      public:
        virtual void load(const std::string& filename) final;
        virtual void unload(const std::string& filename) final;
        virtual std::shared_ptr<Asset> getAsset(const std::string& filename) const final;

      private:
        std::unordered_map<std::string, sf::Font> fonts;
    };
} // simple2dengine

#endif // _SIMPLE2DENGINE_MANAGERS_LOADERS_FONT_LOADER_H_
