/*!
 * @file di_component.hpp
 * @author sangwon lee (leeh8911@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-04-29
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef DI_COMPONENT_HPP_
#define DI_COMPONENT_HPP_

#include <SDL.h>

#include <memory>
#include <vector>

#include "src/math.hpp"

namespace gmlib
{
class IComponent
{
 public:
    virtual ~IComponent() = default;

    virtual void update(Real /* deltaTime */) = 0;
    virtual void render(SDL_Renderer* renderer) = 0;

 private:
};

using ComponentPtr = std::shared_ptr<IComponent>;
using ComponentWeakPtr = std::weak_ptr<IComponent>;
using ComponentList = std::vector<ComponentPtr>;

} // namespace gmlib

#endif // DI_COMPONENT_HPP_
