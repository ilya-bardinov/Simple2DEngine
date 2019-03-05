/**
 * @file canvas_node.h
 * @author Ilya Bardinov (ilya.bardinov@gmail.com)
 * @brief Canvas Node
 * @date 2019-03-05
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef _SIMPLE2DENGINE_NODES_CANVAS_CANVAS_NODE_H_
#define _SIMPLE2DENGINE_NODES_CANVAS_CANVAS_NODE_H_

#include <string>

#include "simple2dengine/engine.h"
#include "simple2dengine/nodes/node.h"

namespace simple2dengine
{
    /**
     * @brief Anchor bit flags for setAnchor.
     *
     * @see CanvasNode.
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

    /**
     * @brief Canvas node.
     * Used for drawing, transforming, positioning.
     *
     */
    class CanvasNode : public Node
    {
      public:
        /**
         * @brief Construct a new Canvas Node.
         *
         * @param engineRef reference to Engine object.
         * @param nodeName name of the node.
         *
         * @see Engine.
         * @see Node.
         */
        CanvasNode(Engine& engineRef, const std::string& nodeName);
        /**
         * @brief Set position of Node.
         *
         * @param position x and y coordinates relative to its parent.
         */
        void setPosition(const sf::Vector2f& position);
        /**
         * @brief Move Node on specified coordinates.
         *
         * @param position x and y coordinate relative to its parent.
         */
        void move(const sf::Vector2f& position);
        /**
         * @brief Get position of Node relative to parent.
         *
         * @return const Vector2f& x and y coordinate relative to parent.
         */
        const sf::Vector2f& getPosition() const;
        /**
         * @brief Get global position of Node.
         *
         * @return const Vector2f& x and y coordinate relative to window (global position).
         */
        const sf::Vector2f& getGlobalPosition() const;
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
         * @brief Check if Node or it parents are visible or not.
         * If someone of Node or its parents is invisible - return value will be false.
         *
         * @return bool visibility of Node or it parents.
         */
        bool isVisibleInTree() const;
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
        Anchor getAnchor() const;
        /**
         * @brief Update Canvas node transform to correctly draw it.
         *
         */
        virtual void updateTransform();

      private:
        bool visible = true; // visibility of node
        Anchor anchor = Anchor::Top | Anchor::Left; // anchor of node
        sf::Vector2f position = sf::Vector2f(0.0f, 0.0f); // position that relative to parents
        sf::Vector2f globalPosition = sf::Vector2f(0.0f, 0.0f); // global position
    };
} // namespace simple2dengine

#endif // _SIMPLE2DENGINE_NODES_CANVAS_CANVAS_NODE_H_
