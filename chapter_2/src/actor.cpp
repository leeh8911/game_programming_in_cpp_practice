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
void Actor::update(Real deltaTime)
{
    for (auto& component : m_Components)
    {
        component->update(deltaTime);
    }
}

void Actor::addComponent(ComponentPtr component)
{
    m_Components.emplace_back(component);
}

Actor::State Actor::getState() const
{
    return m_State;
}
} // namespace gmlib
