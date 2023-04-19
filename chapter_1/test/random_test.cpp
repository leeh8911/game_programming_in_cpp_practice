/*!
 * @file random_test.cpp
 * @author sangwon lee (leeh8911@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-04-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "..\..\chapter_2\src\random.hpp"

#include <gtest/gtest.h>

#include <SFML/Graphics.hpp>
#include <vector>

namespace gmlib
{
TEST(RandomTest, RandomInt)
{

    int value = Random::Uniform(0, 10);
    EXPECT_GE(value, 0);
    EXPECT_LE(value, 10);
}
TEST(RandomTest, RandomVector)
{
    auto value = Random::UniformVector({0, 1, 2}, {2, 3, 4});
    std::vector<int> result(value.begin(), value.end());
    EXPECT_GE(result[0], 0);
    EXPECT_LE(result[0], 2);
    EXPECT_GE(result[1], 1);
    EXPECT_LE(result[1], 3);
    EXPECT_GE(result[2], 2);
    EXPECT_LE(result[2], 4);
}
TEST(RandomTest, RandomSfVector2)
{
    sf::Vector2f value = Random::UniformVector(sf::Vector2f{0, 1}, sf::Vector2f{2, 3});

    EXPECT_GE(value.x, 0);
    EXPECT_LE(value.x, 2);

    EXPECT_GE(value.y, 1);
    EXPECT_LE(value.y, 3);
}
} // namespace gmlib
