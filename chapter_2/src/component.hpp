/*!
 * @file component.hpp
 * @author sangwon lee (leeh8911@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-04-29
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include <SDL.h>

#include "src/actor.hpp"
#include "src/di_component.hpp"

namespace gmlib
{
class Component : public IComponent
{
 public:
    Component(ActorPtr owner) : IComponent(), m_Owner(owner){};

    void update(float /* deltaTime */) override{};
    void render(SDL_Renderer* /*renderer*/) override{};

 private:
};
} // namespace gmlib

#endif // COMPONENT_HPP_
