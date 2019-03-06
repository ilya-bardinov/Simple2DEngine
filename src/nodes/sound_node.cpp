#include "simple2dengine/nodes/sound_node.h"
#include "simple2dengine/managers/asset_manager.h"

namespace simple2dengine
{
    SoundNode::SoundNode(Engine& engineRef, const std::string& nodeName, const std::string& soundFileName)
    : Node(engineRef, nodeName)
    {
        setSound(soundFileName);
    }

    void SoundNode::setSound(const std::string& filename, bool isAssetLoaded/* = true*/)
    {
        if(!isAssetLoaded)
        {
            engine.getAssetManager().load(filename);
        }
        sf::SoundBuffer* buffer = engine.getAssetManager().getAsset<sf::SoundBuffer>(filename);
        if(buffer == nullptr)
        {
            std::cout << "SoundNode::setSound - error in node '" << getName() << "' when loading file '" << filename << "'" << std::endl;
            return;
        }
        setBuffer(*buffer);
    }
} // simple2dengine
