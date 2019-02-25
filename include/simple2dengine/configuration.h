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

namespace simple2dengine
{
    /**
     * @brief Window configuration
     *
     */
    struct Window
    {
        int width = 0; /**< width of window */
        int height = 0; /**< height of window */
        std::string name; /**< name of window */
    };

    /**
     * @brief Configuration Struct
     *
     */
    struct Configuration
    {
        int fps = 0; /**< fps in engine */
        Window window; /**< @see Window. */
    };

} // simple2dengine

#endif // _SIMPLE2DENGINE_CONFIGURATION_H_
