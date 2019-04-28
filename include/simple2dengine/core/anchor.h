/**
 * @file anchor.h
 * @author Ilya Bardinov (ilya.bardinov@gmail.com)
 * @brief
 * @date 2019-03-06
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef _SIMPLE2DENGINE_CORE_ANCHOR_H_
#define _SIMPLE2DENGINE_CORE_ANCHOR_H_

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
    /**
     * @brief bitwise or operation
     *
     * @param a Anchor
     * @param b Anchor
     * @return constexpr enum Anchor Anchor
     */
    constexpr enum Anchor operator|(const enum Anchor a, const enum Anchor b)
    {
        return static_cast<enum Anchor>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
    }
    /**
     * @brief bitwise and operation
     *
     * @param a Anchor
     * @param b Anchor
     * @return constexpr enum Anchor Anchor
     */
    constexpr enum Anchor operator&(const enum Anchor a, const enum Anchor b)
    {
        return static_cast<enum Anchor>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b));
    }
} // namespace simple2dengine

#endif // _SIMPLE2DENGINE_CORE_ANCHOR_H_
