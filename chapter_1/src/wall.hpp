/*!
 * @file wall.hpp
 * @author sangwon lee (leeh8911@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-04-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef SRC_WALL_HPP_
#define SRC_WALL_HPP_

#include <SFML/Graphics.hpp>

namespace gmlib
{

class Wall
{
 public:
    Wall();
    ~Wall();

    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition() const;
    void setSize(sf::Vector2f size);
    sf::Vector2f getSize() const;

 private:
    sf::Vector2f mPosition{0.F, 0.F};
    sf::Vector2f mSize{0.F, 0.F};
};
}  // namespace gmlib

#endif  // SRC_WALL_HPP_
