/*!
 * @file player.cpp
 * @author sangwon lee (leeh8911@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-04-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "src/player.hpp"

#include <SFML/Graphics.hpp>

#include "player.hpp"

namespace gmlib
{
Player::Player() {}

Player::~Player() {}

void Player::setPosition(sf::Vector2f position) { mPosition = position; }

sf::Vector2f Player::getPosition() const { return mPosition; }

void Player::setSize(sf::Vector2f size) { mSize = size; }

sf::Vector2f Player::getSize() const { return mSize; }

void Player::move(Movement movement)
{
    switch (movement)
    {
        case Movement::kUp:
            mPosition.y -= 10.0f;
            break;
        case Movement::kDown:
            mPosition.y += 10.0f;
            break;
    }
}

}  // namespace gmlib
