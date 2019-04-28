/**
 * @file sound_loader.h
 * @author Ilya Bardinov (ilya.bardinov@gmail.com)
 * @brief Sound Loader
 * @date 2019-02-22
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef _SIMPLE2DENGINE_MANAGERS_LOADERS_SOUND_LOADER_H_
#define _SIMPLE2DENGINE_MANAGERS_LOADERS_SOUND_LOADER_H_

#include <memory>
#include <string>
#include <unordered_map>

#include "simple2dengine/managers/loaders/loader.h"

#include "SFML/Audio/SoundBuffer.hpp"

namespace simple2dengine
{
    /**
     * @brief Sound Loader
     *
     */
    class SoundLoader : public Loader
    {
      public:
        /**
         * @brief Load asset with name.
         *
         * @param filename name of asset.
         */
        virtual void load(const std::string& filename) final;
        /**
         * @brief Unload asset with name.
         *
         * @param filename name of asset.
         */
        virtual void unload(const std::string& filename) final;
        /**
         * @brief Get loaded asset with name.
         *
         * @param filename name of asset.
         * @return laoded asset
         */
        virtual const BaseAsset* getAsset(const std::string& filename) const final;

      private:
        std::unordered_map<std::string, sf::SoundBuffer> buffers; // loaded sound buffers
    };
} // namespace simple2dengine

#endif // _SIMPLE2DENGINE_MANAGERS_LOADERS_SOUND_LOADER_H_
