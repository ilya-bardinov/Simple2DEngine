/**
 * @file asset_manager.h
 * @author Ilya Bardinov (ilya.bardinov@gmail.com)
 * @brief Asset Manager
 * @date 2019-02-20
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef _SIMPLE2DENGINE_MANAGERS_ASSET_MANAGER_H_
#define _SIMPLE2DENGINE_MANAGERS_ASSET_MANAGER_H_

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "simple2dengine/managers/loaders/loader.h"

namespace simple2dengine
{
    /**
     * @brief Asset Manager.
     * You can get it from Engine.
     *
     * @see Engine.
     */
    class AssetManager
    {
      public:
        /**
         * @brief Register loader for specific file extension.
         *
         * @param loader loader
         * @param extensions vector of extensions
         *
         * @see Loader.
         */
        void registerLoader(std::shared_ptr<Loader> loader,
                            const std::vector<std::string>& extensions);
        /**
         * @brief Load an Asset
         *
         * @param filename path to asset
         */
        void load(const std::string& filename);
        /**
         * @brief Unload an Asset
         *
         * @param filename path to asset
         */
        void unload(const std::string& filename);
        /**
         * @brief Get loaded Asset.
         *
         * @tparam T Asset class name
         * @param filename path to asset
         * @return const T* loaded asset
         */
        template<class T> const T* getAsset(const std::string& filename) const
        {
            std::shared_ptr<Loader> loader = getLoader(filename);
            if(!loader)
            {
                std::cout << "Error when getting asset '" << filename
                          << "': no loaders found for extension!" << std::endl;
                return nullptr;
            }

            BaseAsset* asset = loader->getAsset(filename);
            if(asset)
            {
                Asset<T>* loadedAsset = static_cast<Asset<T>*>(asset);
                if(loadedAsset != nullptr)
                {
                    const T* ret_asset = loadedAsset->asset;
                    delete asset;
                    return ret_asset;
                }
            }

            return nullptr;
        }
        /**
         * @brief Get the Loader object
         *
         * @param filename loader for a specific file extensions
         * @return loader
         *
         * @see Loader
         */
        std::shared_ptr<Loader> getLoader(const std::string& filename) const;

      private:
        std::unordered_map<std::string, std::shared_ptr<Loader>> loaders; // all loaders
    };
} // namespace simple2dengine

#endif // _SIMPLE2DENGINE_MANAGERS_ASSET_MANAGER_H_
