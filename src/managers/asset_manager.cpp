#include "simple2dengine/managers/asset_manager.h"

namespace simple2dengine
{
    void AssetManager::registerLoader(std::shared_ptr<Loader> loader, const std::vector<std::string>& extensions)
    {
        for(const std::string& extension : extensions)
        {
            auto loaderIterator = loaders.find(extension);
            if(loaderIterator != loaders.end())
            {
                std::cout << "Error when register loader with extension '" << extension << "': extensions has already added!" << std::endl;
                continue;
            }
            loaders[extension] = std::move(loader);
        }
    }

    void AssetManager::load(const std::string& filename)
    {
        std::shared_ptr<Loader> loader = getLoader(filename);
        if(!loader)
        {
            std::cout << "Error when loading asset '" << filename << "': no loaders found for extension!" << std::endl;
            return;
        }

        loader->load(filename);
    }

    void AssetManager::unload(const std::string& filename)
    {
        std::shared_ptr<Loader> loader = getLoader(filename);
        if(!loader)
        {
            std::cout << "Error when unload asset '" << filename << "': no loaders found for extension!" << std::endl;
            return;
        }

        loader->unload(filename);
    }

    std::shared_ptr<Loader> AssetManager::getLoader(const std::string& filename) const
    {
        size_t found = filename.rfind(".");
        std::string extension("");

        if (found != std::string::npos)
        {
            extension = filename.substr(found + 1);
        }

        auto loaderIterator = loaders.find(extension);
        if(loaderIterator != loaders.end())
            return loaderIterator->second;

        return nullptr;
    }
}
