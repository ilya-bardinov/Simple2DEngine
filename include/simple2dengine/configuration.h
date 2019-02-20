/**
 * @file configuration.h
 * @author Ilya Bardinov (ilya.bardinov@gmail.com)
 * @brief Starting class.
 * @version 0.1
 * @date 2019-02-20
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef SIMPLE2DENGINE_CONFIGURATION_H_
#define SIMPLE2DENGINE_CONFIGURATION_H_

#include <string>

namespace simple2dengine
{
struct Window
{
    int width = 0;
    int height = 0;
    std::string name;
};

struct Configuration
{
    int fps = 0;
    Window window;
};
} // simple2dengine

#endif // SIMPLE2DENGINE_CONFIGURATION_H_
