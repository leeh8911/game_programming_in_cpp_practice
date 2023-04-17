/*!
 * @file game.hpp
 * @author sangwon lee (leeh8911@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-04-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef SRC_GAME_HPP_
#define SRC_GAME_HPP_

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "src/object.hpp"

namespace gmlib
{
class Drawer
{
 public:
    Drawer() = default;
    Drawer(const std::shared_ptr<sf::RenderWindow>& windowPtr);

    void setWindowPtr(const std::shared_ptr<sf::RenderWindow>& windowPtr);

    void draw(const Object& object) const;

 private:
    std::shared_ptr<sf::RenderWindow> mWindowPtr{nullptr};
};

class Solver
{
 public:
    Solver() = default;

    void solve(std::vector<std::shared_ptr<Object>>& objects, std::shared_ptr<Object> ball, float deltaTime);

    bool isColliding(Object& first, Object& second);

 private:
    void solveCollision(std::vector<std::shared_ptr<Object>>& objects, std::shared_ptr<Object> ball);

    void solveCollision(Object& first, Object& second);
};

class Game
{
    enum class State
    {
        kReady,
        kPlay,
        kPause,
        kScore,
        kGameOver,
    };

 public:
    Game() = default;

    bool initialize();
    void runLoop();
    void shutdown();

 private:
    void initializeGameObjects();
    void processInput();
    void movePlayer(std::shared_ptr<Object> player, sf::Vector2f movement);
    void updateGame();
    void generateOutput();

    bool mIsRunning{false};
    State mState{State::kReady};

    std::shared_ptr<sf::RenderWindow> mWindowPtr{nullptr};
    std::shared_ptr<Drawer> mDrawerPtr{nullptr};
    std::shared_ptr<Solver> mSolverPtr{nullptr};
    sf::Clock mClock{};

    std::vector<std::shared_ptr<Object>> mObjectPtrList{};
    std::shared_ptr<Object> mPlayer1Ptr{nullptr};
    std::shared_ptr<Object> mPlayer2Ptr{nullptr};
    std::shared_ptr<Object> mBallPtr{nullptr};
    std::vector<std::shared_ptr<Object>> mWallPtrList{};
};
} // namespace gmlib

#endif // SRC_GAME_HPP_
