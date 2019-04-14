/**
 * @file music_node.h
 * @author Ilya Bardinov (ilya.bardinov@gmail.com)
 * @brief Music Node
 * @date 2019-02-27
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef _SIMPLE2DENGINE_NODES_MUSIC_NODE_H_
#define _SIMPLE2DENGINE_NODES_MUSIC_NODE_H_

#include <string>

#include "SFML/Audio/Music.hpp"

#include "simple2dengine/engine.h"
#include "simple2dengine/nodes/node.h"

namespace simple2dengine
{
    /**
     * @brief Streamed music node played from an audio file.
     *
     */
    class MusicNode : public Node, public sf::Music
    {
      public:
        using Node::Node;
        /**
         * @brief Construct a new Music Node.
         *
         * @param nodeName name of the node.
         * @param musicFileName Name of music file with relative or full path.
         *
         * @see Engine.
         * @see Node.
         */
        MusicNode(const std::string& nodeName, const std::string& musicFileName);
    };
} // namespace simple2dengine

#endif // _SIMPLE2DENGINE_NODES_MUSIC_NODE_H_
