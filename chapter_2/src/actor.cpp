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

namespace gmlib
{
void Actor::update(float deltaTime)
{
    for (auto& component : m_Components)
    {
        component->update(deltaTime);
    }
}

void Actor::render(SDL_Renderer* renderer)
{
    for (auto& component : m_Components)
    {
        component->render(renderer);
    }
}

void Actor::addComponent(ComponentPtr component)
{
    m_Components.emplace_back(component);
}

} // namespace gmlib
