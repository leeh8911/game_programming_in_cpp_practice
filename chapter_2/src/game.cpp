/*!
 * @file game.cpp
 * @author sangwon lee (leeh8911@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-04-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "src/game.hpp"

#include <SDL.h>

#include <algorithm>
#include <iostream>

#include "game.hpp"
#include "src/math.hpp"

namespace gmlib
{
Game::Game()
{
}

Game::~Game()
{
}

bool Game::initialize()
{
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResult != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    m_Window = SDL_CreateWindow("Game Programming", 100, 100, 1024, 768, 0);
    if (m_Window == nullptr)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    return true;
}

void Game::runLoop()
{

    while (m_IsRunning)
    {
        processInput();

        Real currentTime = static_cast<Real>(SDL_GetTicks());
        Real deltaTime = (currentTime - m_TickCount) / 1000.0_real;
        m_TickCount = currentTime;

        updateGame(deltaTime);

        generateOutput();
    }
}

void Game::processInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            m_IsRunning = false;
            break;
        }
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE])
    {
        m_IsRunning = false;
    }
}

void Game::addActor(ActorPtr actor)
{
    if (m_UpdatingActors)
    {
        m_PendingActors.emplace_back(actor);
    }
    else
    {
        m_Actors.emplace_back(actor);
    }
}

void Game::updateGame(Real deltaTime)
{
    m_UpdatingActors = true;

    for (auto actor : m_Actors)
    {
        actor->update(deltaTime);
    }
    m_UpdatingActors = false;

    for (auto pending : m_PendingActors)
    {
        m_Actors.emplace_back(pending);
    }
    m_PendingActors.clear();

    auto count = std::count_if(m_Actors.begin(), m_Actors.end(),
                               [](ActorPtr actor) { return actor->getState() == Actor::State::e_Dead; });
    std::vector<ActorPtr> deadActors{};
    deadActors.reserve(count);

    for (auto actor : m_Actors)
    {
        if (actor->getState() == Actor::State::e_Dead)
        {
            deadActors.emplace_back(std::move(actor));
        }
    }
    deadActors.clear();
}

void Game::generateOutput()
{
    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 255, 255);
    SDL_RenderClear(m_Renderer);
    SDL_RenderPresent(m_Renderer);
}

void Game::shutdown()
{
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}
} // namespace gmlib
