/*!
 * @file drawer.cpp
 * @author sangwon lee (leeh8911@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-04-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "src/drawer.hpp"

#include <SFML/Graphics.hpp>

#include "drawer.hpp"
#include "src/object.hpp"

namespace gmlib
{

void Drawer::draw(std::shared_ptr<sf::RenderWindow> windowPtr, const Object& object)
{
    sf::RectangleShape shape;
    shape.setPosition(object.getPosition());
    shape.setSize(object.getSize());
    shape.setFillColor(object.getColor());
    windowPtr->draw(shape);
}

} // namespace gmlib
