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

#include "src/actor.hpp"

namespace gmlib
{
class Game
{
 public:
    Game();
    ~Game();

    bool initialize();
    void runLoop();
    void shutdown();

 private:
    void addActor(ActorPtr actor);

    void processInput();
    void updateGame(Real deltaTime);
    void generateOutput();

    bool m_IsRunning{true};
    SDL_Window* m_Window{nullptr};
    SDL_Renderer* m_Renderer{nullptr};

    Real m_TickCount{0.0_real};
    ActorList m_Actors{};
    ActorList m_PendingActors{};
    bool m_UpdatingActors{false};
};
} // namespace gmlib

#endif // GAME_HPP_
