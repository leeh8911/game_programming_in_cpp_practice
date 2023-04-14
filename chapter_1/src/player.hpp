/*!
 * @file player.hpp
 * @author sangwon lee (leeh8911@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-04-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <SFML/Graphics.hpp>

namespace gmlib
{
class Player
{
 public:
    enum class Movement
    {
        kUp,
        kDown
    };
    Player();
    ~Player();

    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition() const;
    void setSize(sf::Vector2f size);
    sf::Vector2f getSize() const;

    void move(Movement movement);

 private:
    sf::Vector2f mPosition{0.0f, 0.0f};
    sf::Vector2f mSize{20.F, 200.F};
};

}  // namespace gmlib

#endif  // PLAYER_HPP_
