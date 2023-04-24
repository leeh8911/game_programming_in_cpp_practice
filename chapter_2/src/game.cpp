/*!
 * @file game.cpp
 * @author sangwon lee (leeh8911@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-04-25
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "src/game.hpp"

namespace gmlib
{
bool Game::initialize()
{
    bool success{true};

    if (this->mWindow.isOpen())
    {
        success = false;
    }
    else
    {
        this->mWindow.create(sf::VideoMode(1024, 768), "Game");
    }

    return success;
}

void Game::runLoop()
{
    sf::Clock clock{};
    while (this->mIsRunning)
    {
        this->processInput();

        this->update(clock.restart().asSeconds());

        this->generateOutput();
    }
}

void Game::shutdown()
{
    this->mWindow.close();
}

void Game::processInput()
{
    sf::Event event;

    while (this->mWindow.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            this->mIsRunning = false;
            break;
        }
    }
}

void Game::update(float dt)
{
    for (auto& actor : this->mActors)
    {
        actor->update(dt);
    }
}

void Game::generateOutput()
{
    this->mWindow.clear();

    this->mWindow.display();
}

void Game::addActor(ActorPtr actor)
{
    auto iter = std::find(this->mActors.begin(), this->mActors.end(), actor);

    if (iter == this->mActors.end())
    {
        this->mActors.emplace_back(actor);
    }
}
void Game::removeActor(ActorPtr actor)
{
    auto iter = std::find(this->mActors.begin(), this->mActors.end(), actor);

    if (iter != this->mActors.end())
    {
        this->mActors.erase(iter);
    }
}
} // namespace gmlib
