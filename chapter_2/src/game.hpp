/*!
 * @file game.hpp
 * @author sangwon lee (leeh8911@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-04-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef GAME_HPP_
#define GAME_HPP_

#include <SDL.h>

#include <memory>
#include <string>
#include <unordered_map>

#include "src/actor.hpp"
#include "src/component.hpp"
#include "src/di_component.hpp"

namespace gmlib
{
class Game : public std::enable_shared_from_this<Game>
{
 public:
    Game();
    ~Game();

    bool initialize();
    void runLoop();
    void shutdown();

    void addActor(ActorPtr actor);
    void removeActor(ActorPtr actor);

    void addSprite(SpritePtr sprite);
    void removeSprite(SpritePtr sprite);

    SDL_Texture* getTexture(const std::string& fileName);

 private:
    void processInput();
    void updateGame(Real deltaTime);
    void generateOutput();

    void loadData();
    void unloadData();

    std::unordered_map<std::string, SDL_Texture*> m_Textures{};

    bool m_IsRunning{true};
    bool m_UpdatingActors{false};

    SDL_Window* m_Window{nullptr};
    SDL_Renderer* m_Renderer{nullptr};

    Real m_TickCount{0.0_real};
    ActorList m_Actors{};
    ActorList m_PendingActors{};
    SpriteList m_Sprites{};

    ShipPtr m_Ship{nullptr};
};
} // namespace gmlib

#endif // GAME_HPP_
