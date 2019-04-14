/**
 * @file timer_node.h
 * @author Ilya Bardinov (ilya.bardinov@gmail.com)
 * @brief Timer Node.
 * @date 2019-02-26
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef _SIMPLE2DENGINE_NODES_TIMER_NODE_H_
#define _SIMPLE2DENGINE_NODES_TIMER_NODE_H_

#include <functional>
#include <string>

#include "simple2dengine/engine.h"
#include "simple2dengine/nodes/node.h"

namespace simple2dengine
{
    /**
     * @brief Timer Node.
     * Used to set timer and execute command on timer finish.
     *
     */
    class TimerNode : public Node
    {
      public:
        /**
         * @brief Construct a new Time Node.
         *
         * @param nodeName name of the node.
         *
         * @see Engine.
         * @see Node.
         */
        TimerNode(const std::string& nodeName, unsigned int time = 0, bool isOneShot = true)
            : Node(nodeName), finishTime(time), oneShot(isOneShot){};
        /**
         * @brief Set finish time.
         *
         * @param time - time until onTimeout will be called.
         */
        void setTime(unsigned int time);
        /**
         * @brief Start timer.
         *
         */
        void start();
        /**
         * @brief Pause timer.
         *
         */
        void pause();
        /**
         * @brief Reset timer to 0.
         *
         */
        void reset();
        /**
         * @brief Check if timer is paused.
         *
         * @return bool pause or not.
         */
        bool isPaused() const;
        /**
         * @brief Set timer to one shot.
         *
         * @param oneShot if true - one shot timer.
         */
        void setOneShot(bool oneShot);
        /**
         * @brief Check if timer is one shot.
         *
         * @return bool one shot or not.
         */
        bool isOneShot() const;
        /**
         * @brief Store a function that will be called when timeout happens.
         * For example you can use it like this:
         *
         * timer->onTimeout([this] () {
         *     sound->stop();
         *     text->setText("Lose!");
         * });
         *
         * @param function lambda function
         */
        void onTimeout(std::function<void()> function);

      protected:
        /**
         * @brief Override base update().
         * We need to calculate.
         *
         * @see Node.
         */
        virtual void update(int deltaInMs) override;

      private:
        unsigned int finishTime = 0;  // amount of time need to send finish signal
        unsigned int elapsedTime = 0; // current elapsed time
        bool oneShot = true;          // if true - timer will not restart
        bool paused = false;          // if pause if true - time will not elapse

        std::function<void()> timeoutFunc; // signal on timeout
    };
} // namespace simple2dengine

#endif // _SIMPLE2DENGINE_NODES_TIMER_NODE_H_
