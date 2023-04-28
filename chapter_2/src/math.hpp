/*!
 * @file math.hpp
 * @author sangwon lee (leeh8911@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-04-29
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef MATH_HPP_
#define MATH_HPP_

#include <cmath>

namespace gmlib
{

struct Vector2
{
    float x, y;
};

class Math
{
 public:
    class Vector2
    {
     public:
        inline static constexpr ::gmlib::Vector2 s_Zero{0.0f, 0.0f};
    };
};
} // namespace gmlib
#endif // MATH_HPP_
