#include "simple2dengine/nodes/timer_node.h"

namespace simple2dengine
{
    void TimerNode::setTime(unsigned int time)
    {
        finishTime = time;
    }

    void TimerNode::start()
    {
        paused = false;
    }

    void TimerNode::pause()
    {
        paused = true;
    }

    void TimerNode::reset()
    {
        elapsedTime = 0;
    }

    bool TimerNode::isPaused() const
    {
        return paused;
    }

    void TimerNode::setOneShot(bool _oneShot)
    {
        this->oneShot = _oneShot;
    }

    bool TimerNode::isOneShot() const
    {
        return oneShot;
    }

    void TimerNode::onTimeout(std::function<void()> function)
    {
        timeoutFunc = std::move(function);
    }

    void TimerNode::update(unsigned int deltaInMs)
    {
        if(!paused && finishTime > 0)
        {
            if(elapsedTime < finishTime)
            {
                elapsedTime += deltaInMs;
            }
            else
            {
                if(oneShot)
                {
                    paused = true;
                }
                elapsedTime = 0;

                if(timeoutFunc)
                    timeoutFunc();
            }
        }

        Node::update(deltaInMs);
    }
} // simple2dengine
