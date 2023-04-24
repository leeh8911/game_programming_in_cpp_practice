/*!
 * @file component.cpp
 * @author sangwon lee (leeh8911@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-04-25
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "src/component.hpp"

#include "src/actor.hpp"

namespace gmlib
{

Component::Component(Actor* owner, int updateOrder) : mOwner{owner}, mUpdateOrder{updateOrder}
{
    this->mOwner->addComponent(this);
}

Component::~Component()
{
    this->mOwner->removeComponent(this);
}

void Component::update(float dt)
{
}

void Component::render(sf::RenderTarget& target)
{
}

int Component::getUpdateOrder() const
{
    return this->mUpdateOrder;
}

void Component::setUpdateOrder(int order)
{
    this->mUpdateOrder = order;
}

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder) : Component{owner}, mDrawOrder{drawOrder}
{
}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::update(float dt)
{
}

void SpriteComponent::render(sf::RenderTarget& target)
{
    target.draw(this->mSprite);
}

void SpriteComponent::setTexture(sf::Texture* texture)
{
    this->mSprite.setTexture(*texture);
}

sf::Vector2f SpriteComponent::getTexturePosition() const
{
    return this->mSprite.getPosition();
}

sf::Vector2f SpriteComponent::getTextureSize() const
{
    return sf::Vector2f{this->mSprite.getTexture()->getSize()};
}

void SpriteComponent::setDrawOrder(int order)
{
    this->mDrawOrder = order;
}

int SpriteComponent::getDrawOrder() const
{
    return this->mDrawOrder;
}

} // namespace gmlib
