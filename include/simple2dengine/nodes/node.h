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

#ifndef _SIMPLE2DENGINE_NODES_NODE_H_
#define _SIMPLE2DENGINE_NODES_NODE_H_

#include <memory>
#include <vector>

#include "SFML/System/Vector2.hpp"

namespace simple2dengine
{
    class Engine;
    /**
     * @brief Base node class.
     *
     */
    class Node : public std::enable_shared_from_this<Node>
    {
      public:
        /**
         * @brief Construct a new Node.
         *
         */
        Node(Engine& engineRef) : engine(engineRef) { };

        virtual ~Node() { };

        virtual void onCreate() { };
        virtual void onEnter() { };
        virtual void onUpdate(int /*deltaInMs*/) { };
        virtual void onExit() { };
        virtual void onDestroy() { };

        void addChild(std::shared_ptr<Node> child);
        void removeChild(std::shared_ptr<Node> child);

        std::shared_ptr<Node> getParent() const;
        std::shared_ptr<Node> getRoot();

        virtual void setPosition(const sf::Vector2f& position);
        void move(const sf::Vector2f& position);
        const sf::Vector2f& getPosition() const;
        sf::Vector2f getAbsolutePosition() const;

        void setVisible(bool isVisible);
        bool isVisible() const;
        bool isAbsoluteVisible() const;

      protected:
        /**
         * @brief Update logic of engine
         *
         * @param deltaInMs delta time from previous update in milliseconds
         */
        virtual void update(int deltaInMs);
        /**
         * @brief Render and Display scene.
         *
         */
        virtual void render();

        void notifyCreate();
        void notifyEnter();
        void notifyExit();
        void notifyDestroy();

        // engine refer
        Engine& engine;

      private:
        // all child nodes
        std::vector<std::shared_ptr<Node>> children;
        // parent node
        std::weak_ptr<Node> parent;
        // position
        sf::Vector2f position;

        bool visible = true;

        friend class SceneManager;
    };
} // simple2dengine

#endif // _SIMPLE2DENGINE_NODES_NODE_H_
