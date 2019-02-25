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
     * @brief Sound node.
     * Used to manipulate by sounds.
     *
     */
    class SoundNode : public Node
    {
      public:
        /**
         * @brief Construct a new Sound Node.
         *
         * @param engineRef reference to Engine object.
         * @param nodeName name of the node.
         *
         * @see Engine.
         * @see Node.
         */
        SoundNode(Engine& engineRef, const std::string& nodeName) : Node(engineRef, nodeName) { };
        /**
         * @brief Set sound source to Node.
         *
         * @param filename Name of file with relative or full path.
         * @param isAssetLoaded If true - we assume that file is already loaded in asset manager, if false - asset manager will load it before using.
         *
         * @see AssetManager.
         */
        void setSound(const std::string& filename, bool isAssetLoaded = true);

        /**
         * @brief Play loaded sound.
         *
         */
        void play();
        /**
         * @brief Pause loaded sound.
         *
         */
        void pause();
        /**
         * @brief Stop loaded sound.
         *
         */
        void stop();

      private:
        sf::Sound sound;
    };
} // namespace simple2dengine

#endif // _SIMPLE2DENGINE_NODES_SOUND_NODE_H_
