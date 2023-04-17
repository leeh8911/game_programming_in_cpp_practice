/*!
 * @file drawer.hpp
 * @author sangwon lee (leeh8911@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-04-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef DRAWER_HPP_
#define DRAWER_HPP_

#include <SFML/Graphics.hpp>

#include "src/object.hpp"

namespace gmlib
{

class Drawer
{
 public:
    Drawer() = default;
    ~Drawer() = default;

    Drawer(const Drawer& other) = default;
    Drawer(Drawer&& other) noexcept = default;
    Drawer& operator=(const Drawer& other) = default;
    Drawer& operator=(Drawer&& other) noexcept = default;

    void draw(std::shared_ptr<sf::RenderWindow> windowPtr, const Object& object);
};

} // namespace gmlib

#endif // DRAWER_HPP_
