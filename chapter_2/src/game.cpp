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
#include <SDL_image.h>

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

void Game::removeActor(ActorPtr actor)
{
    auto iter = std::find(m_PendingActors.begin(), m_PendingActors.end(), actor);
    if (iter != m_PendingActors.end())
    {
        std::iter_swap(iter, m_PendingActors.end() - 1);
        m_PendingActors.pop_back();
    }

    iter = std::find(m_Actors.begin(), m_Actors.end(), actor);
    if (iter != m_Actors.end())
    {
        std::iter_swap(iter, m_Actors.end() - 1);
        m_Actors.pop_back();
    }
}

void Game::removeSprite(SpritePtr sprite)
{
    auto iter = std::find(m_Sprites.begin(), m_Sprites.end(), sprite);
    if (iter != m_Sprites.end())
    {
        std::iter_swap(iter, m_Sprites.end() - 1);
        m_Sprites.pop_back();
    }
}

void Game::addSprite(SpritePtr sprite)
{
    int myDrawOrder = sprite->getDrawOrder();

    auto iter = m_Sprites.begin();
    for (; iter != m_Sprites.end(); ++iter)
    {
        if (myDrawOrder < (*iter)->getDrawOrder())
        {
            break;
        }
    }

    m_Sprites.insert(iter, sprite);
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

void Game::loadData()
{
    m_Ship = std::make_shared<Ship>(this->shared_from_this());
    m_Ship->setPosition(Vector2{100.0_real, 768.0_real / 2.0_real});
    m_Ship->setScale(1.5_real);

    ActorPtr backgroundActor = std::make_shared<Actor>(this->shared_from_this());
    backgroundActor->setPosition(Vector2{512.0_real, 384.0_real});
    BackgroundPtr bg = std::make_shared<Background>(backgroundActor);
    std::vector<SDL_Texture*> bgTextures = {getTexture("assets/Farback01.png"), getTexture("assets/Farback02.png")};
    bg->setTexture(bgTextures);
    bg->setScrollSpeed(-100.0_real);

    bg = std::make_shared<Background>(backgroundActor);
    bgTextures = {getTexture("assets/Stars.png"), getTexture("assets/Stars.png")};
    bg->setTexture(bgTextures);
    bg->setScrollSpeed(-200.0_real);
}

void Game::unloadData()
{
    while (!m_Actors.empty())
    {
        m_Actors.pop_back();
    }

    for (auto i : m_Textures)
    {
        SDL_DestroyTexture(i.second);
    }
    m_Textures.clear();
}

void Game::generateOutput()
{
    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 255, 255);
    SDL_RenderClear(m_Renderer);
    SDL_RenderPresent(m_Renderer);
}

void Game::shutdown()
{
    unloadData();
    IMG_Quit();

    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}
SDL_Texture* Game::getTexture(const std::string& fileName)
{
    SDL_Texture* tex = nullptr;
    auto iter = m_Textures.find(fileName);
    if (iter != m_Textures.end())
    {
        tex = iter->second;
    }
    else
    {
        SDL_Surface* surf = IMG_Load(fileName.c_str());
        if (!surf)
        {
            SDL_Log("Failed to load texture file %s", fileName.c_str());
            return nullptr;
        }

        tex = SDL_CreateTextureFromSurface(m_Renderer, surf);
        SDL_FreeSurface(surf);
        if (!tex)
        {
            SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
            return nullptr;
        }
        m_Textures.emplace(fileName.c_str(), tex);
    }
    return tex;
}
} // namespace gmlib
