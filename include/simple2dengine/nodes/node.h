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

#ifndef SIMPLE2DENGINE_NODES_NODE_H_
#define SIMPLE2DENGINE_NODES_NODE_H_

#include <memory>
#include <vector>

namespace simple2dengine
{
    class Engine;
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
        Node(Engine& engine);

        virtual ~Node();

        virtual void load();
        virtual void unload();

        void addChild(const std::shared_ptr<Node>& child);
        void removeChild(const std::shared_ptr<Node>& child);
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

      protected:
        // engine refer
        Engine& engine;

      private:
        // all child nodes
        std::vector<std::shared_ptr<Node>> children;
    };
} // simple2dengine

#endif // SIMPLE2DENGINE_NODES_NODE_H_
