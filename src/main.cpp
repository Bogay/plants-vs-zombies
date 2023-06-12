#include <iostream>
#include <string>
// #include "map.h"
// #include "plants.h"
// #include "zombie.h"
// #include "player.h"
#include "game.h"
using namespace std;

int main()
{
    Game game;
    game.init_plants("plant.txt");
    game.print_title();
    // input num_land
    // input num_zombie
    game.print_Rule();
    system("pause");

    // game.init_all_location();
    while (1) 
    {
        int result = game.game_round();
        if(result)
        {
            break;
        }
    }

    return 0;
}