/**
 * @file scene_manager.h
 * @author Ilya Bardinov (ilya.bardinov@gmail.com)
 * @brief Scene Manager
 * @version 0.1
 * @date 2019-02-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef SIMPLE2DENGINE_SCENES_SCENE_MANAGER_H_
#define SIMPLE2DENGINE_SCENES_SCENE_MANAGER_H_

#include <list>
#include <memory>

#include "simple2dengine/scenes/node.h"

namespace simple2dengine
{
    class Node;
    /**
     * @brief Scene Manager.
     * You can get it from node.
     * 
     */
    class SceneManager
    {
      public:
              // allow to construct SceneManager from Engine only. 
        friend class Engine;
        /**
         * @brief Make Node as a current scene.
         * Old Node will be paused.
         * 
         * @param node Node
         */
        void pushScene(std::shared_ptr<Node>& node);
        /**
         * @brief Remove last node.
         * 
         */
        void popScene();
        /**
         * @brief Remove current Node and add a new one.
         * 
         * @param node new that will be added
         */
        void replaceScene(std::shared_ptr<Node>& node);
        /**
         * @brief Get the Scenes Count.
         * 
         * @return int Scenes Count
         */
        int getScenesCount() const;

      private:
        /**
         * @brief Construct a new Scene Manager object.
         * Used for internal purpose.
         * 
         */
        SceneManager();
        /**
         * @brief Update logic of engine
         * 
         * @param deltaInMs delta time from previous update in milliseconds
         */
        void update(int64_t deltaInMs);
        /**
         * @brief Render and Display scene.
         * 
         */
        void render();

      private:
        std::list<std::shared_ptr<Node>> nodes;
    };
} // simple2dengine

#endif // SIMPLE2DENGINE_SCENES_SCENE_MANAGER_H_