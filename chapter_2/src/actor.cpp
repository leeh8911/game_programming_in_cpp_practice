/*!
 * @file actor.cpp
 * @author sangwon lee (leeh8911@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-04-29
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "src/actor.hpp"

#include "src/math.hpp"

namespace gmlib
{

Actor::Actor(GamePtr game) : m_Game(game)
{
}
void Actor::update(Real deltaTime)
{
    for (auto& component : m_Components)
    {
        component->update(deltaTime);
    }
}

void Actor::updateActor(Real /* deltaTime */)
{
}

void Actor::addComponent(ComponentPtr component)
{
    m_Components.emplace_back(component);
}
void Actor::setPosition(const Vector2& position)
{
    m_Position = position;
}

void Actor::setScale(Real scale)
{
    m_Scale = scale;
}

void Actor::setRotation(Real rotation)
{
    m_Rotation = rotation;
}

Vector2 Actor::getPosition() const
{
    return m_Position;
}
Actor::State Actor::getState() const
{
    return m_State;
}

Real Actor::getScale() const
{
    return m_Scale;
}

Real Actor::getRotation() const
{
    return m_Rotation;
}

Ship::Ship(GamePtr game) : Actor(game)
{
}

void Ship::updateActor(Real /*  deltaTime */)
{
}
} // namespace gmlib
