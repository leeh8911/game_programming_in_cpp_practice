/*!
 * @file actor.hpp
 * @author sangwon lee (leeh8911@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-04-29
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef ACTOR_HPP_
#define ACTOR_HPP_

#include <memory>
#include <vector>

#include "src/di_component.hpp"
#include "src/math.hpp"

namespace gmlib
{
class Game;
using GamePtr = std::shared_ptr<Game>;

class Actor
{
 public:
    enum class State
    {
        e_Active,
        e_Pause,
        e_Dead
    };

    Actor(GamePtr game);
    virtual ~Actor() = default;

    void update(Real deltaTime);
    void updateComponents(Real deltaTime);
    virtual void updateActor(Real deltaTime);

    void addComponent(ComponentPtr component);
    void removeComponent(ComponentPtr component);

    State getState() const;

 private:
    Vector2 m_Position{Math::Vector2::s_Zero};
    Real m_Scale{1.0_real};
    Real m_Rotation{0.0_real};

    State m_State{State::e_Active};

    ComponentList m_Components{};
    GamePtr m_Game{nullptr};
};

using ActorPtr = std::shared_ptr<Actor>;
using ActorWeakPtr = std::weak_ptr<Actor>;
using ActorList = std::vector<ActorPtr>;

} // namespace gmlib

#endif // ACTOR_HPP_
