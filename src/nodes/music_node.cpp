#include "simple2dengine/nodes/music_node.h"

namespace simple2dengine
{
    MusicNode::MusicNode(const std::string& nodeName, const std::string& musicFileName)
        : Node(nodeName)
    {
        openFromFile(musicFileName);
    }
} // namespace simple2dengine
