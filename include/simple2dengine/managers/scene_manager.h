/**
 * @file scene_manager.h
 * @author Ilya Bardinov (ilya.bardinov@gmail.com)
 * @brief Scene Manager
 * @date 2019-02-17
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef _SIMPLE2DENGINE_MANAGERS_SCENE_MANAGER_H_
#define _SIMPLE2DENGINE_MANAGERS_SCENE_MANAGER_H_

#include <unordered_map>
#include <memory>
#include <string>
#include <vector>

#include "simple2dengine/nodes/node.h"

namespace simple2dengine
{
    /**
     * @brief Scene Manager.
     * You can get it from Engine.
     *
     * @see Engine.
     */
    class SceneManager
    {
      public:
        /**
         * @brief Construct a new Scene Manager object.
         *
         */
        SceneManager() : currentScene(nullptr) { };
        /**
         * @brief Add node to scene manager.
         *
         * @param name Assign name to scene.
         * @param node Node to add.
         */
        void addScene(const std::string& name, std::shared_ptr<Node> scene);
        /**
         * @brief Remove node with a name.
         *
         * @param name Name of scene to delete.
         */
        void removeScene(const std::string& name);
        /**
         * @brief Activate scene with a name.
         * Activated scene will be displaying on a next tick.
         *
         * @param name Name of scene.
         */
        void activateScene(const std::string& name);
        /**
         * @brief Get the Scenes Count.
         *
         * @return int Scenes Count
         */
        int getSceneCount() const;
        /**
         * @brief Safely remove and notify all scenes.
         *
         */
        void clear();

      private:
        /**
         * @brief Update logic of engine
         *
         * @param deltaInMs delta time from previous update in milliseconds
         */
        void update(unsigned int deltaInMs);
        /**
         * @brief Render and Display scene.
         *
         */
        void render();
        /**
         * @brief Process input events from SFML.
         *
         * @param event input event.
         */
        void input(Event event);

      private:
        std::shared_ptr<Node> currentScene; // current scene
        std::unordered_map<std::string, std::shared_ptr<Node>> scenes; // all nodes (scenes)
        std::vector<std::shared_ptr<Node>> destroyedScenes; // nodes that will be destroyed on next tick

        friend class Engine;
    };
} // simple2dengine

#endif // _SIMPLE2DENGINE_MANAGERS_SCENE_MANAGER_H_
