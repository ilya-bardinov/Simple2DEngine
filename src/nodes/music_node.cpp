#include "simple2dengine/nodes/music_node.h"

namespace simple2dengine
{
    MusicNode::MusicNode(Engine& engineRef, const std::string& nodeName, const std::string& musicFileName)
    : Node(engineRef, nodeName)
    {
        openFromFile(musicFileName);
    }
} // simple2dengine
