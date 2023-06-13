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
    constexpr static int max_num_zombie = 10;
    constexpr static int max_num_land = 10;
    constexpr static int default_num_zombie = 3;
    constexpr static int default_num_land = 8;
    
    std::vector<Plants*> all_plants() const;

    Game(std::string num_land, std::string num_zombie);
    static void print_title();
    void print_Rule() const;
    int init_plants_setting(const std::string fileName);
    void init_all_location();

    void print_map() const;
    void print_zombieInfo() const;
    void print_choice_option() const;
    void print_player_money() const;

    int player_Choice();
    void visit_plant(Plants *plant);
    int zombie_action(std::vector<Zombie*> &all_zombies);
    void player_move();
    int game_round();
    int win_or_lose() const;

private:
    constexpr static int player_v = 6;
    constexpr static int zombie_v = 3;
    constexpr static int zombie_hp = 40;
    constexpr static int zombie_atk = 15;
    constexpr static int default_money = 150;

    
    int num_land_ = 0;
    int num_plant_ = 0;
    int num_bombPlant_ = 0;
    int num_zombie_ = 0;
    int lowest_price_ = 999999;
    int default_choice_ = 0;
    int choice_ = default_choice_;
    mutable std::map<int, std::string> plants_map_;

    int cur_zombie_num_ = 0;
    Map *map_ = nullptr;
    Player *player_ = nullptr;
    std::vector<Plants*>& all_plants_ = *new std::vector<Plants*>;
    std::vector<Zombie*>& all_zombies_ = *new std::vector<Zombie*>;
};

#endif
