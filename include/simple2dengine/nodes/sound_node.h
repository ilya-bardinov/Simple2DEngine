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
         * @brief Construct a new Sound Node.
         *
         * @param engineRef reference to Engine object.
         * @param nodeName name of the node.
         * @param soundFileName Name of sound file with relative or full path.
         *
         * @see Engine.
         * @see Node.
         */
        SoundNode(Engine& engineRef, const std::string& nodeName, const std::string& soundFileName);
        /**
         * @brief Set the source file containing the audio data to play.
         *
         * @param filename Name of file with relative or full path.
         * @param isAssetLoaded If true - we assume that file is already loaded in asset manager, if false - asset manager will load it before using.
         *
         * @see AssetManager.
         */
        void setSound(const std::string& filename, bool isAssetLoaded = true);
    };
} // namespace simple2dengine

#endif // _SIMPLE2DENGINE_NODES_SOUND_NODE_H_
