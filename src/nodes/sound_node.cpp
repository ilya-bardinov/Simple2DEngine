#include "simple2dengine/nodes/sound_node.h"
#include "simple2dengine/managers/asset_manager.h"

namespace simple2dengine
{
    void SoundNode::setSound(const std::string& filename, bool isAssetLoaded/* = true*/)
    {
        if(!isAssetLoaded)
        {
            engine.getAssetManager().load(filename);
        }
        sf::SoundBuffer* buffer = engine.getAssetManager().getAsset<sf::SoundBuffer>(filename);
        if(buffer == nullptr)
        {
            std::cout << "SoundNode::setSound - error when loading file " << filename << std::endl;
            return;
        }
        sound.setBuffer(*buffer);
    }

    void SoundNode::play()
    {
        sound.play();
    }

    void SoundNode::pause()
    {
        sound.pause();
    }

    void SoundNode::stop()
    {
        sound.stop();
    }
}
