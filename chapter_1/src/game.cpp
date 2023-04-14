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
#include <memory>
#include <string>
#include <unordered_map>

#include "src/player.hpp"

namespace gmlib
{
bool Game::initialize()
{
    mWindowPtr = std::make_shared<sf::RenderWindow>(
        sf::VideoMode(1024, 768), "Game Programming in C++ (Chapter 1)");
    mWindowPtr->setFramerateLimit(60);

    mIsRunning = true;

    mPlayer = Player();
    sf::Vector2f windowPosition =
        static_cast<sf::Vector2f>(mWindowPtr->getPosition());
    float margin = 10.F;
    mPlayer.setPosition({margin, windowPosition.y / 2});

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
                    mPlayer.move(Player::Movement::kUp);
                }
                if (event.key.code == sf::Keyboard::S)
                {
                    mPlayer.move(Player::Movement::kDown);
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

void Game::generateOutput()
{
    mWindowPtr->clear(sf::Color::Black);

    sf::Vector2f playerPosition = mPlayer.getPosition();
    sf::Vector2f playerSize = mPlayer.getSize();

    sf::RectangleShape playerShape;
    playerShape.setPosition(playerPosition + playerSize / 2.F);
    playerShape.setSize(playerSize);
    playerShape.setFillColor(sf::Color::White);

    mWindowPtr->draw(playerShape);

    mWindowPtr->display();
}
}  // namespace gmlib
