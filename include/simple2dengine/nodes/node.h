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
#include <string>

#include "SFML/System/Vector2.hpp"

namespace simple2dengine
{
    typedef sf::Vector2<int>          Vector2i;
    typedef sf::Vector2<unsigned int> Vector2u;
    typedef sf::Vector2<float>        Vector2f;

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
        Node(Engine& engineRef, const std::string& nodeName) : engine(engineRef), name(nodeName) { };

        virtual ~Node() { };

        virtual void onCreate() { };
        virtual void onEnter() { };
        virtual void onUpdate(int /*deltaInMs*/) { };
        virtual void onExit() { };
        virtual void onDestroy() { };

        void addChild(std::shared_ptr<Node> child);
        void removeChild(std::shared_ptr<Node> child);

        const std::string& getName() const;

        std::shared_ptr<Node> getParent() const;
        std::shared_ptr<Node> getRoot();
        std::shared_ptr<Node> getNode(const std::string& path);

        virtual void setPosition(const Vector2f& position);
        void move(const Vector2f& position);
        const Vector2f& getPosition() const;
        Vector2f getAbsolutePosition() const;

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
        Vector2f position;
        // name of node
        std::string name;

        bool visible = true;

        friend class SceneManager;
    };
} // simple2dengine

#endif // _SIMPLE2DENGINE_NODES_NODE_H_
