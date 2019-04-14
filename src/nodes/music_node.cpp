#include "simple2dengine/nodes/music_node.h"

namespace simple2dengine
{
    void MusicNode::setMusic(const std::string& filename)
    {
        openFromFile(filename);
    }
} // namespace simple2dengine
