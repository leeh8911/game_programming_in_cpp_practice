/*!
 * @file object.hpp
 * @author sangwon lee (leeh8911@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-04-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <SFML/Graphics.hpp>

namespace gmlib
{

class Object
{
 public:
    virtual ~Object() = default;
    Object() = default;

    Object(const Object& other) = default;
    Object(Object&& other) noexcept = default;
    Object& operator=(const Object& other) = default;
    Object& operator=(Object&& other) noexcept = default;

    Object& setPosition(sf::Vector2f position);
    Object& setVelocity(sf::Vector2f velocity);
    Object& setSize(sf::Vector2f size);
    Object& setColor(sf::Color color);

    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;
    sf::Vector2f getSize() const;
    sf::Color getColor() const;

 private:
    sf::Vector2f mPosition{0.F, 0.F};
    sf::Vector2f mVelocity{0.F, 0.F};
    sf::Vector2f mSize{0.F, 0.F};
    sf::Color mColor{sf::Color::White};
};

class Player : public Object
{
 public:
    enum class Movement
    {
        kUp,
        kDown
    };
    ~Player() override = default;
    Player() = default;

    void move(Movement movement);

 private:
};

class Wall : public Object
{
 public:
    ~Wall() override = default;
    Wall() = default;

 private:
};

class Ball : public Object
{
 public:
    ~Ball() override = default;
    Ball() = default;

 private:
};
} // namespace gmlib

#endif // OBJECT_HPP_
