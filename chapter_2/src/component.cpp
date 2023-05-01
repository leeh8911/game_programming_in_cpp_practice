/*!
 * @file component.cpp
 * @author sangwon lee (leeh8911@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-04-29
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "src/component.hpp"

#include "component.hpp"
#include "src/actor.hpp"
#include "src/math.hpp"

namespace gmlib
{

Component::Component(ActorPtr owner) : m_Owner(owner)
{
}

void Component::update(Real /* deltaTime */)
{
}

int64_t Component::getUpdateOrder() const
{
    return m_UpdateOrder;
}

ActorWeakPtr Component::getOwner() const
{
    return m_Owner;
}

Sprite::Sprite(ActorPtr owner, int drawOrder) : Component(owner), m_DrawOrder(drawOrder)
{
}

void Sprite::render(SDL_Renderer* renderer)
{
    if (m_Texture)
    {
        SDL_Rect r;
        auto owner = this->getOwner().lock();
        r.w = static_cast<int>(m_TextureWidth * owner->getScale());
        r.h = static_cast<int>(m_TextureHeight * owner->getScale());
        r.x = static_cast<int>(owner->getPosition().x - r.w / 2);
        r.y = static_cast<int>(owner->getPosition().y - r.h / 2);

        SDL_RenderCopyEx(renderer, m_Texture, nullptr, &r, -Math::toDegrees(owner->getRotation()), nullptr,
                         SDL_FLIP_NONE);
    }
}

void Sprite::setTexture(SDL_Texture* texture)
{
    m_Texture = texture;
    SDL_QueryTexture(texture, nullptr, nullptr, &m_TextureWidth, &m_TextureHeight);
}

int Sprite::getTextureHeight() const
{
    return m_TextureHeight;
}

int Sprite::getTextureWidth() const
{
    return m_TextureWidth;
}

int Sprite::getDrawOrder() const
{
    return m_DrawOrder;
}

Animation::Animation(ActorPtr owner, int drawOrder) : Sprite(owner, drawOrder)
{
}

void Animation::update(Real deltaTime)
{
    Sprite::update(deltaTime);

    if (m_Frames.empty())
    {
        return;
    }

    Real frameSize = static_cast<Real>(m_Frames.size());

    m_CurrentFrame += m_AnimFPS * deltaTime;
    while (m_CurrentFrame >= frameSize)
    {
        m_CurrentFrame -= frameSize;
    }

    setTexture(m_Frames[static_cast<int>(m_CurrentFrame)]);
}

void Animation::setAnimation(const std::vector<SDL_Texture*>& frames)
{
    m_Frames.resize(frames.size());
    std::copy(frames.begin(), frames.end(), m_Frames.begin());
    m_CurrentFrame = 0;
    setTexture(m_Frames[0]);
}

Real Animation::getAnimFPS() const
{
    return m_AnimFPS;
}

void Animation::setAnimFPS(Real fps)
{
    m_AnimFPS = fps;
}

Background::Background(ActorPtr owner, int drawOrder) : Sprite(owner, drawOrder)
{
}

void Background::update(Real deltaTime)
{
    Sprite::update(deltaTime);

    for (auto& background : m_Textures)
    {
        background.offset.x -= m_ScrollSpeed * deltaTime;
        if (background.offset.x < -m_ScreenSize.x)
        {
            background.offset.x = (m_Textures.size() - 1) * m_ScreenSize.x - 1;
        }
    }
}

void Background::render(SDL_Renderer* renderer)
{
    for (auto& background : m_Textures)
    {
        SDL_Rect r;
        r.w = static_cast<int>(m_ScreenSize.x);
        r.h = static_cast<int>(m_ScreenSize.y);
        r.x = static_cast<int>(background.offset.x);
        r.y = static_cast<int>(background.offset.y);

        SDL_RenderCopy(renderer, background.texture, nullptr, &r);
    }
}

void Background::setTexture(const std::vector<SDL_Texture*>& textures)
{
    int count = 0;
    for (auto tex : textures)
    {
        BGTexture temp;
        temp.texture = tex;

        temp.offset.x = count * m_ScreenSize.x;
        temp.offset.y = 0;
        m_Textures.emplace_back(temp);
        count++;
    }
}

} // namespace gmlib
