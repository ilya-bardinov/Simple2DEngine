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
#include <vector>
#include <iostream>

#include "simple2dengine/managers/loaders/loader.h"

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
        void registerLoader(std::shared_ptr<Loader> loader, const std::vector<std::string>& extensions);

        void load(const std::string& filename);
        void unload(const std::string& filename);

      private:
        template <class T>
        T* getAsset(const std::string& filename) const
        {
            std::shared_ptr<Loader> loader = getLoader(filename);
            if(!loader)
            {
                std::cout << "Error when getting asset '" << filename << "': no loaders found for extension!" << std::endl;
                return nullptr;
            }

            std::shared_ptr<Asset> asset = loader->getAsset(filename);
            if(asset != nullptr)
            {
                return static_cast<T *>(asset->nativeAsset);
            }
            return nullptr;
        }

        std::shared_ptr<Loader> getLoader(const std::string& filename) const;

      private:
        std::unordered_map<std::string, std::shared_ptr<Loader>> loaders;

        friend class SpriteNode;
        friend class SoundNode;
        friend class TextNode;
    };
} // simple2dengine

#endif // SIMPLE2DENGINE_MANAGERS_ASSET_MANAGER_H_
