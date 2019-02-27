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
#include "simple2dengine/nodes/sound_node.h"

namespace simple2dengine
{
    /**
     * @brief Streamed music played from an audio file.
     *
     */
    class MusicNode : public Node
    {
      public:
        /**
         * @brief Construct a new Music Node.
         *
         * @param engineRef reference to Engine object.
         * @param nodeName name of the node.
         *
         * @see Engine.
         * @see Node.
         */
        MusicNode(Engine& engineRef, const std::string& nodeName) : Node(engineRef, nodeName) { };
        /**
         * @brief Open a music from an audio file.
         *
         * @param filename Name of file with relative or full path.
         *
         */
        void setMusic(const std::string& filename);
        /**
         * @brief Get the total duration of the music
         *
         * @return Music duration
         *
         */
        sf::Time getDuration() const;
        /**
         * @brief Start or resume playing the sound.
         *
         * This function starts the stream if it was stopped, resumes
         * it if it was paused, and restarts it from beginning if it
         * was it already playing.
         * This function uses its own thread so that it doesn't block
         * the rest of the program while the sound is played.
         *
         * @see pause, stop
         *
         */
        void play();
        /**
         * @brief Pause the sound.
         *
         * This function pauses the sound if it was playing,
         * otherwise (sound already paused or stopped) it has no effect.
         *
         * @see play, stop
         *
         */
        void pause();
        /**
         * @brief stop playing the sound.
         *
         * This function stops the sound if it was playing or paused,
         * and does nothing if it was already stopped.
         * It also resets the playing position (unlike pause()).
         *
         * @see play, pause.
         *
         */
        void stop();
        /**
         * @brief Set whether or not the sound should loop after reaching the end.
         *
         * If set, the sound will restart from beginning after
         * reaching the end and so on, until it is stopped or
         * setLoop(false) is called.
         * The default looping state for sound is false.
         *
         * @param loop True to play in loop, false to play once.
         *
         * @see getLoop
         *
         */
        void setLoop(bool loop);
        /**
         * @brief Tell whether or not the sound is in loop mode.
         *
         * @return True if the sound is looping, false otherwise.
         *
         * @see setLoop
         *
         */
        bool getLoop() const;
        /**
         * @brief Get the current status of the sound (stopped, paused, playing).
         *
         * @return Current status of the sound
         *
         */
        Status getStatus() const;

      private:
        sf::Music music;
    };
} // namespace simple2dengine

#endif // _SIMPLE2DENGINE_NODES_MUSIC_NODE_H_
