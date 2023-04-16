/*!
 * @file random.cpp
 * @author sangwon lee (leeh8911@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-04-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "src/random.hpp"

namespace gmlib
{

std::random_device RandomGenerator::mRandomDevice{};
std::mt19937 RandomGenerator::mGenerator{};

} // namespace gmlib
