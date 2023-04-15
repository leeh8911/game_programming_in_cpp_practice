/*!
 * @file game.cpp
 * @author sangwon lee (leeh8911@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-04-14
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "src/game.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "src/player.hpp"
#include "src/wall.hpp"

namespace gmlib
{
bool Game::initialize()
{
    mWindowPtr = std::make_shared<sf::RenderWindow>(
        sf::VideoMode(1024, 768), "Game Programming in C++ (Chapter 1)");
    mWindowPtr->setFramerateLimit(60);

    mIsRunning = true;

    sf::Vector2f windowSize = static_cast<sf::Vector2f>(mWindowPtr->getSize());
    float margin = windowSize.x * 0.1F;
    mPlayers.first.setPosition({margin, windowSize.y / 2});
    mPlayers.second.setPosition({windowSize.x - margin, windowSize.y / 2});

    float wallMargin = windowSize.y * 0.1F;
    float wallHeight = wallMargin / 2.F;
    mWalls.resize(2);
    mWalls[0].setPosition({0, wallMargin});
    mWalls[0].setSize({windowSize.x, wallHeight});
    mWalls[1].setPosition({0, windowSize.y - wallHeight});
    mWalls[1].setSize({windowSize.x, wallHeight});

    return true;
}

void Game::runLoop()
{
    mClock.restart();

    while (mIsRunning)
    {
        processInput();

        updateGame();
        mClock.restart();

        generateOutput();
    }
}

void Game::shutdown() { mIsRunning = false; }

void Game::processInput()
{
    sf::Event event;
    while (mWindowPtr->pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                {
                    mIsRunning = false;
                }
                if (event.key.code == sf::Keyboard::W)
                {
                    mPlayers.first.move(Player::Movement::kUp);
                }
                if (event.key.code == sf::Keyboard::S)
                {
                    mPlayers.first.move(Player::Movement::kDown);
                }
                if (event.key.code == sf::Keyboard::Up)
                {
                    mPlayers.second.move(Player::Movement::kUp);
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    mPlayers.second.move(Player::Movement::kDown);
                }
                break;
            case sf::Event::Closed:
                mIsRunning = false;
                break;
        }
    }
}

void Game::updateGame()
{
    // auto delta_time = mClock.getElapsedTime().asSeconds();
}

void Game::drawPlayer(const Player& player) const
{
    sf::Vector2f playerPosition = player.getPosition();
    sf::Vector2f playerSize = player.getSize();

    sf::RectangleShape playerShape;
    playerShape.setPosition(playerPosition - playerSize / 2.F);
    playerShape.setSize(playerSize);
    playerShape.setFillColor(sf::Color::White);

    mWindowPtr->draw(playerShape);
}

void Game::drawWall(const Wall& wall) const
{
    sf::Vector2f wallPosition = wall.getPosition();
    sf::Vector2f wallSize = wall.getSize();

    sf::RectangleShape wallShape;
    wallShape.setPosition(wallPosition);
    wallShape.setSize(wallSize);
    wallShape.setFillColor(sf::Color::Blue);

    mWindowPtr->draw(wallShape);
}

void Game::generateOutput()
{
    mWindowPtr->clear(sf::Color::Black);

    drawPlayer(mPlayers.first);
    drawPlayer(mPlayers.second);

    for (const auto& wall : mWalls)
    {
        drawWall(wall);
    }

    mWindowPtr->display();
}
}  // namespace gmlib
