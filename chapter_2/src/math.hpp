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

using Real = float;

constexpr Real operator""_real(long double value)
{
    return static_cast<Real>(value);
}

} // namespace gmlib

namespace gmlib
{

struct Vector2
{
    Real x, y;
};

class Math
{
 public:
    class Vector2
    {
     public:
        inline static constexpr ::gmlib::Vector2 s_Zero{0.0_real, 0.0_real};
    };
};
} // namespace gmlib
#endif // MATH_HPP_
