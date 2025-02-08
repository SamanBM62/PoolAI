#include "Game/game.hpp"
#include <iostream>

int main()
{
    Game game{};

    while (game.running())
    {

        //update
        game.update();

        //render
        game.render();

        // window.clear();
        // window.display();
    }
}
