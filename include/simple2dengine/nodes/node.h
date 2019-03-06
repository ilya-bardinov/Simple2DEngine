/**
 * @file node.h
 * @author Ilya Bardinov (ilya.bardinov@gmail.com)
 * @brief Base node.
 * @date 2019-02-17
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef _SIMPLE2DENGINE_NODES_NODE_H_
#define _SIMPLE2DENGINE_NODES_NODE_H_

#include <memory>
#include <vector>
#include <string>

#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/Rect.hpp"

namespace simple2dengine
{
    /**
     * @brief Current state of Node in Scene Manager.
     *
     * @see SceneManager
     * @see Node
     *
     */
    enum class NodeState : unsigned int
    {
        None,
        Creating,
        Entering,
        Updating,
        Exiting,
        Destroying
    };

    class Engine;
    /**
     * @brief Base node class.
     * Used everywhere in Engine.
     * Before run engine loop you should create any node and activate it in engine.
     *
     */
    class Node : public std::enable_shared_from_this<Node>
    {
      public:
        /**
         * @brief Construct a new Node with ref to engine and with name.
         *
         * @param engineRef reference to Engine object.
         * @param nodeName name of the node.
         *
         * @see Engine.
         */
        Node(Engine& engineRef, const std::string& nodeName) : engine(engineRef), name(nodeName) { };

        /**
         * @brief Destroy the Node object
         *
         */
        virtual ~Node() { };

        /**
         * @brief Notifier.
         * Will be called when node or it parent added to scene manager.
         *
         * @see SceneManager
         *
         */
        virtual void onCreate() { };
        /**
         * @brief Notifier.
         * Will be called when node or in parent activated (become current) in scene manager.
         *
         * @see SceneManager
         *
         */
        virtual void onEnter() { };
        /**
         * @brief Notifier.
         * Will be called on every tick when node or it parent is active in scene manager.
         *
         * @see SceneManager
         *
         */
        virtual void onUpdate(int /*deltaInMs*/) { };
        /**
         * @brief Process input events like mouse movement, key press and release, etc.
         *
         * @param event input event.
         *
         * @see SceneManager
         *
         */
        virtual void onInput(sf::Event /*event*/) { };
        /**
         * @brief Notifier.
         * Will be called on every tick when node or it parent became inactive in scene manager.
         *
         * @see SceneManager
         *
         */
        virtual void onExit() { };
        /**
         * @brief Notifier.
         * Will be called on every tick when node or it parent was removed from scene manager.
         *
         * @see SceneManager
         *
         */
        virtual void onDestroy() { };

        /**
         * @brief Add child to node tree.
         *
         * @param child will be added to node tree.
         *
         * @return true if successfully add a node, otherwise return false.
         *
         */
        bool addChild(std::shared_ptr<Node> child);
        /**
         * @brief Remove child from node tree.
         *
         * @param child will be removed from node tree.
         *
         * @return true if successfully add a node, otherwise return false.
         *
         */
        bool removeChild(std::shared_ptr<Node> child);

        /**
         * @brief Get the Name of Node.
         *
         * @return const std::string& name of Node.
         */
        const std::string& getName() const;

        /**
         * @brief Get parent node of Node.
         *
         * @return std::shared_ptr<Node> parent of Node.
         */
        std::shared_ptr<Node> getParent() const;
        /**
         * @brief Get root node of Node.
         *
         * @return std::shared_ptr<Node> root of Node.
         */
        std::shared_ptr<Node> getRoot();
        /**
         * @brief Get all children of Node.
         *
         * @return std::vector<std::shared_ptr<Node>> children.
         */
        const std::vector<std::shared_ptr<Node>>& getChildren() const;
        /**
         * @brief Get node from scene tree by the provided path.
         * Path example: "../player", "../..", "..", "player/sprite", "."
         * ".." - it is a parent of node.
         * "." - current node.
         * "player/sprite" - get child with name "player" in current node, in "player" try to find child with name "sprite".
         *
         * @param path path to Node.
         * @return std::shared_ptr<Node> node in path if it exist, otherwise return nullptr.
         */
        std::shared_ptr<Node> getNode(const std::string& path);

      protected:
        /**
         * @brief Update logic of engine.
         *
         * @param deltaInMs delta time from previous update in milliseconds.
         */
        virtual void update(int deltaInMs);
        /**
         * @brief Render and Display scene.
         *
         */
        virtual void render();

        Engine& engine; // engine reference

      private:
        /**
         * @brief Notification methods.
         * Used by scene manager.
         *
         * @see onCreate().
         */
        void notifyCreate();
        /**
         * @brief Notification methods.
         * Used by scene manager.
         *
         * @see onEnter().
         */
        void notifyEnter();
        /**
         * @brief Notification methods.
         * Used by scene manager.
         *
         * @param event input event.
         *
         * @see onInput().
         *
         */
        void notifyInput(sf::Event event);
        /**
         * @brief Notification methods.
         * Used by scene manager.
         *
         * @see onExit().
         */
        void notifyExit();
        /**
         * @brief Notification methods.
         * Used by scene manager.
         *
         * @see onDestroy().
         */
        void notifyDestroy();

      private:
        std::vector<std::shared_ptr<Node>> children; // all child nodes
        std::weak_ptr<Node> parent; // parent node

        std::string name; // name of node

        NodeState state = NodeState::None; // current state of node

        friend class SceneManager;
    };
} // simple2dengine

#endif // _SIMPLE2DENGINE_NODES_NODE_H_
