#include <iostream>
#include <string>
#include "game.h"
using namespace std;

int main()
{
    Game::print_title();
    string num_land = "", num_zombie = "";

    cout << "Number of lands on the map (1-" << Game::max_num_land
         << ", default: " << Game::default_num_land << ")...>";
    cin >> num_land;

    cout << "Number of zombies on the map (1-" << Game::max_num_zombie
         << ", default: " << Game::default_num_zombie << ")...>";
    cin >> num_zombie;

    Game game(num_land, num_zombie);
    game.init_plants_setting("plant.txt");
    game.print_Rule();

    game.init_all_location();
    while (1)
    {
        int result = game.game_round();
        if (result)
        {
            break;
        }
    }

    return 0;
}