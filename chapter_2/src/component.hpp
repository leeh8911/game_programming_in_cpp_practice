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
#include "src/math.hpp"

namespace gmlib
{
class Component : public IComponent
{
 public:
    Component(ActorPtr owner);

    void update(Real /* deltaTime */) override;

    int64_t getUpdateOrder() const;

    ActorWeakPtr getOwner() const;

 private:
    ActorWeakPtr m_Owner;
    int64_t m_UpdateOrder{100};
};

class Sprite : public Component
{
 public:
    Sprite(ActorPtr owner, int drawOrder = 100);

    void render(SDL_Renderer* renderer) override;

    void setTexture(SDL_Texture* texture);

    int getDrawOrder() const;
    int getTextureWidth() const;
    int getTextureHeight() const;

 protected:
    SDL_Texture* m_Texture{nullptr};
    int m_DrawOrder{100};
    int m_TextureWidth{0};
    int m_TextureHeight{0};
};

using SpritePtr = std::shared_ptr<Sprite>;
using SpriteWeakPtr = std::weak_ptr<Sprite>;
using SpriteList = std::vector<SpritePtr>;

class Animation : public Sprite
{
 public:
    Animation(ActorPtr owner, int drawOrder = 100);

    void update(Real deltaTime) override;

    void setAnimation(const std::vector<SDL_Texture*>& frames);

    void setAnimFPS(Real fps);
    Real getAnimFPS() const;

 private:
    Real m_AnimFPS{24.0_real};
    Real m_CurrentFrame{0.0_real};
    Real m_FrameTime{0.0_real};
    std::vector<SDL_Texture*> m_Frames{};
};

class Background : public Sprite
{
 public:
    Background(ActorPtr owner, int drawOrder = 100);

    void update(Real deltaTime) override;
    void render(SDL_Renderer* renderer) override;

    void setTexture(const std::vector<SDL_Texture*>& textures);
    void setScreenSize(const Vector2& size);

    void setScrollSpeed(Real speed);
    float getScrollSpeed() const;

 private:
    Vector2 m_ScreenSize{0.0_real, 0.0_real};
    Real m_ScrollSpeed{0.0_real};
    struct BGTexture
    {
        SDL_Texture* texture{nullptr};
        Vector2 offset{0.0_real, 0.0_real};
    };
    std::vector<BGTexture> m_Textures{};
};
using BackgroundPtr = std::shared_ptr<Background>;
using BackgroundWeakPtr = std::weak_ptr<Background>;

} // namespace gmlib

#endif // COMPONENT_HPP_
