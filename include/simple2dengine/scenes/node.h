/**
 * @file node.h
 * @author Ilya Bardinov (ilya.bardinov@gmail.com)
 * @brief Base node.
 * @version 0.1
 * @date 2019-02-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef SIMPLE2DENGINE_SCENES_NODE_H_
#define SIMPLE2DENGINE_SCENES_NODE_H_

#include "simple2dengine/scenes/scene_manager.h"

namespace simple2dengine
{
    class SceneManager;
    /**
     * @brief Base node class.
     * 
     */
    class Node
    {
      public:
        /**
         * @brief Construct a new Node.
         * 
         */
        Node();
        /**
         * @brief Update logic of engine
         * 
         * @param deltaInMs delta time from previous update in milliseconds
         */
        void update(int32_t deltaInMs);
        /**
         * @brief Render and Display scene.
         * 
         */
        void render();
        /**
         * @brief Get the SceneManager.
         * 
         * @return SceneManager* for convenient way to add or remove scene from currenet scene. Will be nullptr if scene is not added.
         */
        SceneManager* getSceneManager() const;

      private:
        /**
         * @brief Set the Scene Manager.
         * Used for internal purpose.
         * 
         * @param sceneManager is a SceneManager 
         */
        void setSceneManager(SceneManager* sceneManager);

      private:
        // main scene manager
        SceneManager* sceneManager = nullptr;

        // allow to use setSceneManager when node was added to it. 
        friend class SceneManager;
    };
} // simple2dengine

#endif // SIMPLE2DENGINE_SCENES_NODE_H_