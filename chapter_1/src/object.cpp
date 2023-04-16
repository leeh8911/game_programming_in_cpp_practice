/*!
 * @file object.cpp
 * @author sangwon lee (leeh8911@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-04-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "src/object.hpp"

#include <SFML/Graphics.hpp>

namespace gmlib
{

Object& Object::setPosition(sf::Vector2f position)
{
    mPosition = position;
    return *this;
}
Object& Object::setVelocity(sf::Vector2f velocity)
{
    mVelocity = velocity;
    return *this;
}

Object& Object::setSize(sf::Vector2f size)
{
    mSize = size;
    return *this;
}

Object& Object::setColor(sf::Color color)
{
    mColor = color;
    return *this;
}

sf::Vector2f Object::getPosition() const
{
    return mPosition;
}

sf::Vector2f Object::getVelocity() const
{
    return mVelocity;
}

sf::Vector2f Object::getSize() const
{
    return mSize;
}

sf::Color Object::getColor() const
{
    return mColor;
}

void Player::move(Movement movement)
{
    auto position = getPosition();
    switch (movement)
    {
    case Movement::kUp:
        position.y -= 10.0f;
        break;
    case Movement::kDown:
        position.y += 10.0f;
        break;
    }

    setPosition(position);
}

} // namespace gmlib
