/*!
 * @file wall.cpp
 * @author sangwon lee (leeh8911@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-04-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "src\wall.hpp"

namespace gmlib
{

Wall::Wall() {}

Wall::~Wall() {}

void Wall::setPosition(sf::Vector2f position) { mPosition = position; }

sf::Vector2f Wall::getPosition() const { return mPosition; }

void Wall::setSize(sf::Vector2f size) { mSize = size; }

sf::Vector2f Wall::getSize() const { return mSize; }

}  // namespace gmlib
