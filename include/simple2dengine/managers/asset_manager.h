/**
 * @file asset_manager.h
 * @author Ilya Bardinov (ilya.bardinov@gmail.com)
 * @brief Asset Manager
 * @version 0.1
 * @date 2019-02-20
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef SIMPLE2DENGINE_MANAGERS_ASSET_MANAGER_H_
#define SIMPLE2DENGINE_MANAGERS_ASSET_MANAGER_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <iostream>

#include "SFML/Graphics/Texture.hpp"

namespace simple2dengine
{
    /**
     * @brief Asset Manager.
     * You can get it from Engine.
     *
     */
    class AssetManager
    {
      public:
        sf::Texture loadTexture(const std::string& filename);
        void unloadTexture(const std::string& filename);
        void unloadTextures();

      private:
        std::unordered_map<std::string, sf::Texture> textures;
    };
} // simple2dengine

#endif // SIMPLE2DENGINE_MANAGERS_ASSET_MANAGER_H_
