/*!
 * @file component.hpp
 * @author sangwon lee (leeh8911@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-04-20
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

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

class Component : public std::enable_shared_from_this<Component>
{
 public:
    Component(Actor* owner, int updateOrder = 100);

    virtual ~Component();
    virtual void update(float dt);
    virtual void render(sf::RenderTarget& target);

    int getUpdateOrder() const;
    void setUpdateOrder(int order);

 private:
    ActorPtr mOwner{};
    int mUpdateOrder{};
};

class SpriteComponent : public Component
{
 public:
    SpriteComponent(Actor* owner, int drawOrder = 100);
    ~SpriteComponent();

    void update(float dt) override;
    void render(sf::RenderTarget& target) override;

    void setTexture(sf::Texture* texture);

    sf::Vector2f getTexturePosition() const;
    sf::Vector2f getTextureSize() const;

    void setDrawOrder(int order);
    int getDrawOrder() const;

 private:
    sf::Sprite mSprite{};
    int mDrawOrder{};
};

class AnimateSpriteComponent : public SpriteComponent
{
 public:
    AnimateSpriteComponent(Actor* owner, int drawOrder = 100);
    ~AnimateSpriteComponent();

    void update(float dt) override;
    void render(sf::RenderTarget& target) override;

    void setAnimation(const std::vector<sf::Texture>& textures);

    void setAnimateFps(float fps);
    float getAnimateFps() const;

 private:
    std::vector<sf::Texture> mTextures{};
    float mCurrentFrame{};
    float mAnimateFps{};
};

class BackgroundComponent : public SpriteComponent
{
 public:
    BackgroundComponent(class Actor* owner, int drawOrder = 10);
    void update(float dt) override;
    void render(sf::RenderTarget& target) override;
    void setBackgroundTextures(const std::vector<sf::Texture*>& textures);
    void setScreenSize(const sf::Vector2f& size);
    void setScrollSpeed(float speed);
    float getScrollSpeed() const;

 private:
    struct BackgroundTexture
    {
        sf::Texture* mTexture;
        sf::Vector2f mOffset;
    };
    std::vector<BackgroundTexture> mBackgroundTextures{};
    sf::Vector2f mScreenSize{};
    float mScrollSpeed{};
};
} // namespace gmlib

#endif // COMPONENT_HPP_
