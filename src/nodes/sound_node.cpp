#include "simple2dengine/nodes/sound_node.h"
#include "simple2dengine/managers/asset_manager.h"

namespace simple2dengine
{
    void SoundNode::setSound(const AssetManager& assetManager, const std::string& filename)
    {
        const sf::SoundBuffer* buffer = assetManager.getAsset<sf::SoundBuffer>(filename);
        if(buffer == nullptr)
        {
            std::cout << "SoundNode::setSound - error in node '" << getName()
                      << "' when loading file '" << filename << "'" << std::endl;
            return;
        }
        setBuffer(*buffer);
    }
} // namespace simple2dengine
