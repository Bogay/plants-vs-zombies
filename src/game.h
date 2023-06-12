#ifndef GAME__
#define GAME__

#include <iostream>
#include <string>
#include <map>
#include "map.h"
#include "plants.h"
#include "zombie.h"
#include "player.h"

class Game
{
public:
    Game();
    ~Game();

    void print_title() const;
    void print_Rule() const;
    int init_plants(const std::string fileName);
    void init_all_location();

    void print_map(const Map &) const;
    void print_zombieInfo(const Zombie &) const;
    void print_choice_option() const;
    void print_player_money(const Player &) const;

    void player_Choice();
    void zombie_action(Zombie &);
    void player_move(Player &plant);
    int game_round();
    int win_or_lose() const;

private:
    int default_choice_ = 0;
    int choice_ = default_choice_;
    mutable std::map<int, std::string> plants_;
};

#endif
