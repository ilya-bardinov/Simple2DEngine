/**
 * @file sound_node.h
 * @author Ilya Bardinov (ilya.bardinov@gmail.com)
 * @brief Sound Node
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
     * @brief Regular sound node that can be played in the audio environment.
     *
     */
    class SoundNode : public Node, public sf::Sound
    {
      public:
        using Node::Node;
        /**
         * @brief Set the source file containing the audio data to play.
         *
         * @param assetManager Asset Manager where asset should be stored.
         * @param filename Name of file with relative or full path.
         *
         * @see AssetManager.
         */
        void setSound(const AssetManager& assetManager, const std::string& filename);
    };
} // namespace simple2dengine

#endif // _SIMPLE2DENGINE_NODES_SOUND_NODE_H_
