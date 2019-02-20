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

#ifndef SIMPLE2DENGINE_MANAGERS_SCENE_MANAGER_H_
#define SIMPLE2DENGINE_MANAGERS_SCENE_MANAGER_H_

#include <unordered_map>
#include <memory>
#include <string>

#include "simple2dengine/nodes/node.h"

namespace simple2dengine
{
    class Engine;
    /**
     * @brief Scene Manager.
     * You can get it from Engine.
     *
     */
    class SceneManager
    {
      public:
        /**
         * @brief Construct a new Scene Manager object.
         * Used for internal purpose.
         *
         */
        SceneManager(Engine& engine);
        /**
         * @brief Make Node as a current scene.
         * Old Node will be paused.
         *
         * @param node Node
         */
        void addScene(const std::string& name, const std::shared_ptr<Node>& scene);
        /**
         * @brief Remove last node.
         *
         */
        void removeScene(const std::string& name);
        /**
         * @brief Remove current Node and add a new one.
         *
         * @param node new that will be added
         */
        void switchToScene(const std::string& name);
        /**
         * @brief Get the Scenes Count.
         *
         * @return int Scenes Count
         */
        int getSceneCount() const;
        /**
         * @brief Update logic of engine
         *
         * @param deltaInMs delta time from previous update in milliseconds
         */
        void update(int deltaInMs);
        /**
         * @brief Render and Display scene.
         *
         */
        void render();

      private:
        // engine
        Engine& engine;
        // current scene
        std::shared_ptr<Node> currentScene;
        // map of nodes
        std::unordered_map<std::string, std::shared_ptr<Node>> scenes;
    };
} // simple2dengine

#endif // SIMPLE2DENGINE_MANAGERS_SCENE_MANAGER_H_
