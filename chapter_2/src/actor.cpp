/*!
 * @file actor.cpp
 * @author sangwon lee (leeh8911@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-04-25
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "src/actor.hpp"

namespace gmlib
{

Actor::Actor(GamePtr game) : mGame{game}
{
}

Actor::~Actor()
{
}

void Actor::update(float dt)
{
    if (this->mState == State::kActive)
    {
        this->updateComponents(dt);
        this->updateActor(dt);
    }
}

void Actor::updateComponents(float dt)
{
    for (auto& component : this->mComponents)
    {
        component->update(dt);
    }
}

void Actor::updateActor(float dt)
{
}

void Actor::addComponent(ComponentPtr component)
{
    auto iter = std::find(this->mComponents.begin(), this->mComponents.end(), component);

    if (iter == this->mComponents.end())
    {
        this->mComponents.emplace_back(component);
        std::sort(this->mComponents.begin(), this->mComponents.end(),
                  [](const ComponentPtr& a, const ComponentPtr& b)
                  { return a->getUpdateOrder() < b->getUpdateOrder(); });
    }
}

void Actor::removeComponent(ComponentPtr component)
{
    auto iter = std::find(this->mComponents.begin(), this->mComponents.end(), component);

    if (iter != this->mComponents.end())
    {
        this->mComponents.erase(iter);
    }
}

} // namespace gmlib
