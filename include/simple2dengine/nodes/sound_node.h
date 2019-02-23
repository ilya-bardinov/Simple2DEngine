/**
 * @file sound_node.h
 * @author Ilya Bardinov (ilya.bardinov@gmail.com)
 * @brief Sound Node
 * @version 0.1
 * @date 2019-02-22
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef _SIMPLE2DENGINE_NODES_SOUND_NODE_H_
#define _SIMPLE2DENGINE_NODES_SOUND_NODE_H_

#include <string>

#include "SFML/Audio/Sound.hpp"

#include "simple2dengine/engine.h"
#include "simple2dengine/nodes/node.h"

namespace simple2dengine
{
    /**
     * @brief Sprite node.
    *
    */
    class SoundNode : public Node
    {
      public:
        SoundNode(Engine& engineRef) : Node(engineRef) {  };
        /**
         * @brief add Sound to object.
         *
         * @param filename Name of file with relative or full path
         */
        void setSound(const std::string& filename, bool isAssetLoaded = true);

        void play();
        void pause();
        void stop();

      private:
        sf::Sound sound;
    };
} // namespace simple2dengine

#endif // _SIMPLE2DENGINE_NODES_SOUND_NODE_H_
