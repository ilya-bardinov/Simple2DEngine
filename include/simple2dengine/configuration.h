/**
 * @file configuration.h
 * @author Ilya Bardinov (ilya.bardinov@gmail.com)
 * @brief Configuration class.
 * @date 2019-02-20
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef _SIMPLE2DENGINE_CONFIGURATION_H_
#define _SIMPLE2DENGINE_CONFIGURATION_H_

#include <string>

#include <SFML/Window.hpp>

namespace simple2dengine
{
    /**
     * @brief Window configuration
     *
     */
    struct Window
    {
        unsigned int width = 0;                  /**< width of window, in pixels */
        unsigned int height = 0;                 /**< height of window, in pixels */
        unsigned int bitsPerPixel = 32;          /**< pixel depth, in bits per pixels */
        sf::Vector2i position;                   /**< window position, in pixels */
        unsigned int style = sf::Style::Default; /**< window styles */
        std::string name;                        /**< name of window */
    };
    /**
     * @brief FPS configuation
     *
     * Activating vertical synchronization will limit the number
     * of frames displayed to the refresh rate of
     * the monitor. This can avoid some visual artifacts,
     * and limit the framerate to a good value (but not
     * constant across different computers).
     */
    struct Framerate
    {
        bool verticalSync = false; /**< vertical synchronization, false by default */
        unsigned int fps = 0;      /**< framerate limit (use 0 to disable limit) */
    };
    /**
     * @brief Configuration Struct
     *
     */
    struct Configuration
    {
        Window window;       /**< @see Window. */
        Framerate framerate; /**< @see Framerate. */
    };
} // namespace simple2dengine

#endif // _SIMPLE2DENGINE_CONFIGURATION_H_
