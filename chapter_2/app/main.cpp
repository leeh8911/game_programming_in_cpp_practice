/*!
 * @file main.cpp
 * @author sangwon lee (leeh8911@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-04-14
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "src/game.hpp"

int main(int /* argc */, char** /* argv */)
{
    gmlib::Game game;

    if (game.initialize())
    {
        game.runLoop();
    }

    game.shutdown();

    return 0;
}
