#include "simple2dengine/nodes/music_node.h"

namespace simple2dengine
{
    void MusicNode::setMusic(const std::string& filename)
    {
        if(!music.openFromFile(filename))
        {
            std::cout << "MusicNode::setMusic - error in node '" << getName() << "' when loading file '" << filename << "'" << std::endl;
            return;
        }
    }

    sf::Time MusicNode::getDuration() const
    {
        return music.getDuration();
    }

    void MusicNode::play()
    {
        music.play();
    }

    void MusicNode::pause()
    {
        music.pause();
    }

    void MusicNode::stop()
    {
        music.stop();
    }

    void MusicNode::setLoop(bool loop)
    {
        music.setLoop(loop);
    }

    bool MusicNode::getLoop() const
    {
        return music.getLoop();
    }

    Status MusicNode::getStatus() const
    {
        return music.getStatus();
    }
}
