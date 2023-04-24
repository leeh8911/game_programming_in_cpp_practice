/*!
 * @file game.hpp
 * @author sangwon lee (leeh8911@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-04-25
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef GAME_HPP_
#define GAME_HPP_

#include <SFML/Graphics.hpp>

#include "src/actor.hpp"

namespace gmlib
{
class Game
{
 public:
    Game() = default;
    ~Game() = default;

    bool initialize();
    void runLoop();
    void shutdown();

 private:
    void processInput();
    void update(float dt);
    void generateOutput();

    void addActor(ActorPtr actor);
    void removeActor(ActorPtr actor);

    bool mIsRunning{true};
    sf::RenderWindow mWindow{};

    ActorPtrList mActors{};
};
} // namespace gmlib

#endif // GAME_HPP_
