﻿/*!
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
#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "game.hpp"
#include "src/object.hpp"
#include "src/random.hpp"

namespace gmlib
{
Drawer::Drawer(const std::shared_ptr<sf::RenderWindow>& windowPtr) : mWindowPtr(windowPtr)
{
}

void Drawer::setWindowPtr(const std::shared_ptr<sf::RenderWindow>& windowPtr)
{
    mWindowPtr = windowPtr;
}

void Drawer::draw(const Object& object) const
{
    sf::RectangleShape objectShape;
    objectShape.setPosition(object.getPosition());
    objectShape.setSize(object.getSize());
    objectShape.setFillColor(object.getColor());

    mWindowPtr->draw(objectShape);
}

bool Game::initialize()
{
    mWindowPtr = std::make_shared<sf::RenderWindow>(sf::VideoMode(1024, 768), "Game Programming in C++ (Chapter 1)");
    mWindowPtr->setFramerateLimit(60);

    mDrawerPtr = std::make_shared<Drawer>(mWindowPtr);
    mSolverPtr = std::make_shared<Solver>();

    mIsRunning = true;

    initializeGameObjects();

    return true;
}

void Game::initializeGameObjects()
{
    sf::Vector2f windowSize = static_cast<sf::Vector2f>(mWindowPtr->getSize());
    float margin = windowSize.x * 0.1F;

    mPlayer1Ptr = std::make_shared<Player>();
    mPlayer2Ptr = std::make_shared<Player>();

    mPlayer1Ptr->setSize({20.F, 100.F});
    mPlayer2Ptr->setSize({20.F, 100.F});
    mPlayer1Ptr->setPosition(sf::Vector2f{margin, windowSize.y / 2} - mPlayer1Ptr->getSize() / 2.F);
    mPlayer2Ptr->setPosition(sf::Vector2f{windowSize.x - margin, windowSize.y / 2} - mPlayer2Ptr->getSize() / 2.F);
    mObjectPtrList.emplace_back(mPlayer1Ptr);
    mObjectPtrList.emplace_back(mPlayer2Ptr);

    Wall wall1{};
    Wall wall2{};

    float wallMargin = windowSize.y * 0.1F;
    float wallHeight = wallMargin / 2.F;
    wall1.setSize({windowSize.x, wallHeight});
    wall2.setSize({windowSize.x, wallHeight});
    wall1.setPosition({0, wallMargin});
    wall2.setPosition({0, windowSize.y - wallHeight});
    mObjectPtrList.emplace_back(std::make_shared<Wall>(wall1));
    mObjectPtrList.emplace_back(std::make_shared<Wall>(wall2));

    sf::Vector2f gameViewLeftTop = wall1.getPosition();
    sf::Vector2f gameViewRightBottom = wall2.getPosition() + wall2.getSize();

    Ball ball{};
    ball.setSize({20.F, 20.F});
    ball.setPosition((gameViewLeftTop + gameViewRightBottom) / 2.F);

    float theta = Random::Uniform(0.F, 1.F) > 0.5F ? 0.F : 180.F;
    theta += Random::Uniform(0.F, 1.F) * 30.F - 15.F;
    theta *= 3.141592F / 180.F;
    ball.setVelocity({100.F * std::cos(theta), 100.F * std::sin(theta)});
    mObjectPtrList.emplace_back(std::make_shared<Ball>(ball));
    mBallPtr = mObjectPtrList.back();
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

void Game::shutdown()
{
    mIsRunning = false;
}

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
                mPlayer1Ptr->setPosition(mPlayer1Ptr->getPosition() + sf::Vector2f{0.F, 10.F});
            }
            if (event.key.code == sf::Keyboard::S)
            {
                mPlayer1Ptr->setPosition(mPlayer1Ptr->getPosition() - sf::Vector2f{0.F, 10.F});
            }
            if (event.key.code == sf::Keyboard::Up)
            {
                mPlayer2Ptr->setPosition(mPlayer2Ptr->getPosition() + sf::Vector2f{0.F, 10.F});
            }
            if (event.key.code == sf::Keyboard::Down)
            {
                mPlayer2Ptr->setPosition(mPlayer2Ptr->getPosition() - sf::Vector2f{0.F, 10.F});
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
    auto delta_time = mClock.getElapsedTime().asSeconds();

    mSolverPtr->solve(mObjectPtrList, mBallPtr, delta_time);
}

void Game::generateOutput()
{
    mWindowPtr->clear(sf::Color::Black);

    for (const auto& objectPtr : mObjectPtrList)
    {
        mDrawerPtr->draw(*objectPtr);
    }

    mWindowPtr->display();
}

void Solver::solve(std::vector<std::shared_ptr<Object>>& objects, std::shared_ptr<Object> ball, float deltaTime)
{

    ball->setPosition(ball->getPosition() + ball->getVelocity() * deltaTime);

    solveCollision(objects, ball);
}

void Solver::solveCollision(std::vector<std::shared_ptr<Object>>& objects, std::shared_ptr<Object> ball)
{
    for (auto& objectPtr : objects)
    {
        if ((objectPtr != ball) && isColliding(*ball, *objectPtr))
        {
            solveCollision(*ball, *objectPtr);
        }
    }
}
bool Solver::isColliding(Object& first, Object& second)
{
    auto firstHalfSize = first.getSize() / 2.F;
    auto secondHalfSize = second.getSize() / 2.F;
    auto firstCenter = first.getPosition() + firstHalfSize;
    auto secondCenter = second.getPosition() + secondHalfSize;

    auto diff = firstCenter - secondCenter;
    auto sum = firstHalfSize + secondHalfSize;

    return std::abs(diff.x) < sum.x && std::abs(diff.y) < sum.y;
}

void Solver::solveCollision(Object& first, Object& second)
{
    auto firstHalfSize = first.getSize() / 2.F;
    auto secondHalfSize = second.getSize() / 2.F;
    auto firstCenter = first.getPosition() + firstHalfSize;
    auto secondCenter = second.getPosition() + secondHalfSize;

    auto diff = firstCenter - secondCenter;
    auto sum = firstHalfSize + secondHalfSize;

    if (std::abs(diff.x) > std::abs(diff.y))
    {
        if (diff.x > 0)
        {
            first.setPosition(second.getPosition() + sf::Vector2f{second.getSize().x, 0.F});
        }
        else
        {
            first.setPosition(second.getPosition() - sf::Vector2f{first.getSize().x, 0.F});
        }
        first.setVelocity({-first.getVelocity().x, first.getVelocity().y});
    }
    else
    {
        if (diff.y > 0)
        {
            first.setPosition(second.getPosition() + sf::Vector2f{0.F, second.getSize().y});
        }
        else
        {
            first.setPosition(second.getPosition() - sf::Vector2f{0.F, first.getSize().y});
        }
        first.setVelocity({first.getVelocity().x, -first.getVelocity().y});
    }
}

} // namespace gmlib
