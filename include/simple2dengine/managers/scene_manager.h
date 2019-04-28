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

#include <memory>
#include <string>
#include <unordered_map>
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
        SceneManager() : currentScene(nullptr){};
        /**
         * @brief Add node to scene manager.
         *
         * @param scene - scene to add.
         */
        void addScene(std::shared_ptr<Node> scene);
        /**
         * @brief Remove node with a name immediately.
         * This method is not a safe for deleting.
         *
         * @param scene - scene to delete.
         */
        void removeSceneImmediately(std::shared_ptr<Node> scene);
        /**
         * @brief Add node to erasing queue.
         * Queues a node for deletion at the next frame.
         * When deleted, all of its child nodes will be deleted as well.
         * This method ensures it’s safe to delete the node.
         *
         * @param scene - scene to delete.
         */
        void removeScene(std::shared_ptr<Node> scene);
        /**
         * @brief Activate scene with a name.
         * Activated scene will be displaying on a next tick.
         *
         * @param scene - scene to activate.
         */
        void activateScene(std::shared_ptr<Node> scene);
        /**
         * @brief Get the Scenes Count.
         *
         * @return Scenes Count
         */
        int getScenesCount() const;
        /**
         * @brief Get scene object by name.
         *
         * @param name - Name of scene.
         * @return std::shared_ptr<Node> - pointer to scene.
         */
        std::shared_ptr<Node> getScene(const std::string& name);
        /**
         * @brief Safely remove and notify all scenes.
         *
         */
        void clear();
        /**
         * @brief Update logic of engine
         *
         * @param deltaInMs delta time from previous update in milliseconds
         */
        void update(const int deltaInMs);
        /**
         * @brief Render and Display scene.
         *
         */
        void render();
        /**
         * @brief Process input events from SFML.
         *
         * @param event - input event.
         */
        void input(const sf::Event& event);

      private:
        std::shared_ptr<Node> currentScene = nullptr;                  // current scene
        std::unordered_map<std::string, std::shared_ptr<Node>> scenes; // all scenes (nodes)
        std::vector<std::shared_ptr<Node>> removedScenes; // nodes that will be destroyed on next tick

        Engine* engine = nullptr; // engine pointer

        friend class Engine;
    };
} // namespace simple2dengine

#endif // _SIMPLE2DENGINE_MANAGERS_SCENE_MANAGER_H_
