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

namespace simple2dengine
{
    // it will be more convenient
    using Vector2i = sf::Vector2<int>;
    using Vector2u = sf::Vector2<unsigned int>;
    using Vector2f = sf::Vector2<float>;
    // for input event
    using Event = sf::Event;

    /**
     * @brief Anchor bit flags for setAnchor.
     *
     * @see SpriteNode.
     */
    enum class Anchor : unsigned int
    {
        None = 0,
        Top = 1 << 0,
        Left = 1 << 1,
        Bottom = 1 << 2,
        Right = 1 << 3,
        Center = 1 << 4
    };
    constexpr enum Anchor operator | (const enum Anchor a, const enum Anchor b)
    {
        return static_cast<enum Anchor>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
    }
    constexpr enum Anchor operator & (const enum Anchor a, const enum Anchor b)
    {
        return static_cast<enum Anchor>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b));
    }

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
        virtual void onUpdate(unsigned int /*deltaInMs*/) { };
        /**
         * @brief Process input events like mouse movement, key press and release, etc.
         *
         * @param event input event.
         *
         * @see SceneManager
         *
         */
        virtual void onInput(Event /*event*/) { };
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
         */
        void addChild(std::shared_ptr<Node> child);
        /**
         * @brief Remove child from node tree.
         *
         * @param child will be removed from node tree.
         */
        void removeChild(std::shared_ptr<Node> child);

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

        /**
         * @brief Set position of Node.
         *
         * @param position x and y coordinates relative to its parent.
         */
        void setPosition(const Vector2f& position);
        /**
         * @brief Move Node on specified coordinates.
         *
         * @param position x and y coordinate relative to its parent.
         */
        void move(const Vector2f& position);
        /**
         * @brief Get position of Node.
         *
         * @return const Vector2f& x and y coordinate relative to its parent.
         */
        const Vector2f& getPosition() const;
        /**
         * @brief Get position of Node.
         *
         * @return const Vector2f& x and y coordinate relative to window (so named global position).
         */
        Vector2f getAbsolutePosition() const;

        /**
         * @brief Set visibility of Node.
         * If parent is invisible, curent Node will be invisible too.
         *
         * @param isVisible visibility of Node.
         */
        void setVisible(bool isVisible);
        /**
         * @brief Check if Node is visible or not.
         *
         * @return bool visibility of Node.
         */
        bool isVisible() const;
        /**
         * @brief Check if Node or its parents are visible or not.
         * If someone of Node or its parents is invisible - return value will be false.
         *
         * @return bool visibility of Node or its parents.
         */
        bool isAbsoluteVisible() const;
        /**
         * @brief Set Node anchor.
         *
         * @param anchor anchor.
         */
        void setAnchor(const Anchor anchor);
        /**
         * @brief Get anchor of Node.
         *
         * @return Anchor.
         */
        Anchor getAnchor();
        /**
         * @brief Get size of Node.
         *
         * @return Vector2f width and height of node.
         */
        virtual Vector2f getSize() const;

      protected:
        /**
         * @brief Update logic of engine.
         *
         * @param deltaInMs delta time from previous update in milliseconds.
         */
        virtual void update(unsigned int deltaInMs);
        /**
         * @brief Render and Display scene.
         *
         */
        virtual void render();
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
        void notifyInput(Event event);
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
        /**
         * @brief Update position when node parameters was changed
         *
         */
        virtual void updatePosition();

        Engine& engine; // engine reference

      private:
        std::vector<std::shared_ptr<Node>> children; // all child nodes
        std::weak_ptr<Node> parent; // parent node

        Vector2f position; // position that relative to parents
        std::string name; // name of node
        bool visible = true; // visibility of node
        Anchor anchor = Anchor::Top | Anchor::Left; // anchor of node

        friend class SceneManager;
    };
} // simple2dengine

#endif // _SIMPLE2DENGINE_NODES_NODE_H_
