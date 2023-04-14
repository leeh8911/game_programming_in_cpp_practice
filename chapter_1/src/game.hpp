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

#include "src/player.hpp"

namespace gmlib
{
class Game
{
 public:
    Game() = default;

    bool initialize();
    void runLoop();
    void shutdown();

 private:
    void processInput();
    void updateGame();
    void generateOutput();

    bool mIsRunning{false};
    std::shared_ptr<sf::RenderWindow> mWindowPtr{nullptr};

    Player mPlayer{};
};
}  // namespace gmlib

#endif  // SRC_GAME_HPP_
