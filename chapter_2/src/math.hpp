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

    static Real toDegrees(Real radians)
    {
        return radians * 180.0_real / static_cast<Real>(PI);
    }

    static Real toRadians(Real degrees)
    {
        return degrees * static_cast<Real>(PI) / 180.0_real;
    }

    static constexpr Real PI = 3.1415926535_real;
    static constexpr Real TWO_PI = 2.0_real * PI;
    static constexpr Real HALF_PI = 0.5_real * PI;
};
} // namespace gmlib
#endif // MATH_HPP_
