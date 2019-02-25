/**
 * @file loader.h
 * @author Ilya Bardinov (ilya.bardinov@gmail.com)
 * @brief Base Loader
 * @date 2019-02-21
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef _SIMPLE2DENGINE_MANAGERS_LOADERS_LOADER_H_
#define _SIMPLE2DENGINE_MANAGERS_LOADERS_LOADER_H_

#include <string>
#include <memory>

namespace simple2dengine
{
    /**
     * @brief Base Asset for loader.
     *
     */
    struct Asset
    {
        void *nativeAsset;
    };

    /**
     * @brief Base Loader
     *
     */
    class Loader
    {
      public:
        /**
         * @brief Destroy the Loader object
         *
         */
        virtual ~Loader() = 0;
        /**
         * @brief Load asset with name.
         *
         * @param filename name of asset.
         */
        virtual void load(const std::string& filename) = 0;
        /**
         * @brief Unload asset with name.
         *
         * @param filename name of asset.
         */
        virtual void unload(const std::string& filename) = 0;
        /**
         * @brief Get loaded asset.
         *
         * @param filename name of asset.
         * @return loaded asset.
         */
        virtual std::shared_ptr<Asset> getAsset(const std::string& filename) const = 0;
    };
} // simple2dengine

#endif // _SIMPLE2DENGINE_MANAGERS_LOADERS_LOADER_H_
