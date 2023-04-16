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

 private:
    void solveCollision(std::vector<std::shared_ptr<Object>>& objects, std::shared_ptr<Object> ball);

    bool isColliding(Object& first, Object& second);
    void solveCollision(Object& first, Object& second);
};

class Game
{
 public:
    Game() = default;

    bool initialize();
    void runLoop();
    void shutdown();

 private:
    void initializeGameObjects();
    void processInput();
    void updateGame();
    void generateOutput();
    bool mIsRunning{false};

    std::shared_ptr<sf::RenderWindow> mWindowPtr{nullptr};
    std::shared_ptr<Drawer> mDrawerPtr{nullptr};
    std::shared_ptr<Solver> mSolverPtr{nullptr};
    sf::Clock mClock{};

    std::vector<std::shared_ptr<Object>> mObjectPtrList{};
    std::shared_ptr<Object> mPlayer1Ptr{nullptr};
    std::shared_ptr<Object> mPlayer2Ptr{nullptr};
    std::shared_ptr<Object> mBallPtr{nullptr};
};
} // namespace gmlib

#endif // SRC_GAME_HPP_
