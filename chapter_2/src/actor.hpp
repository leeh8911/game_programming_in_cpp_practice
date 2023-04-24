/*!
 * @file actor.hpp
 * @author sangwon lee (leeh8911@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-04-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef ACTOR_HPP_
#define ACTOR_HPP_

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

namespace gmlib
{

// forward declaration
class Actor;
class Game;
class Component;

// type alias
using ActorPtr = std::shared_ptr<Actor>;
using ComponentPtr = std::shared_ptr<Component>;
using GamePtr = std::shared_ptr<Game>;

using ComponentPtrList = std::vector<ComponentPtr>;
using ActorPtrList = std::vector<ActorPtr>;

class Actor
{
    enum class State
    {
        kActive,
        kPaused,
        kDead
    };

 public:
    Actor(GamePtr game);
    virtual ~Actor();

    void update(float dt);
    void updateComponents(float dt);
    virtual void updateActor(float dt);

    void addComponent(ComponentPtr component);
    void removeComponent(ComponentPtr component);

 private:
    State mState{};

    sf::Vector2f mPosition{};
    float mScale{};
    float mRotation{};

    ComponentPtrList mComponents{};
    GamePtr mGame{};
};
} // namespace gmlib
#endif // ACTOR_HPP_
