/**
 * @file loader.h
 * @author Ilya Bardinov (ilya.bardinov@gmail.com)
 * @brief
 * @version 0.1
 * @date 2019-02-21
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef _SIMPLE2DENGINE_MANAGERS_LOADERS_LOADER_H_
#define _SIMPLE2DENGINE_MANAGERS_LOADERS_LOADER_H_

#include <string>

namespace simple2dengine
{
    struct Asset
    {
        void *nativeAsset;
    };

    class Loader
    {
      public:
        virtual ~Loader() = 0;
        virtual void load(const std::string& filename) = 0;
        virtual void unload(const std::string& filename) = 0;
        virtual std::shared_ptr<Asset> getAsset(const std::string& filename) const = 0;
    };
} // simple2dengine

#endif // _SIMPLE2DENGINE_MANAGERS_LOADERS_LOADER_H_
