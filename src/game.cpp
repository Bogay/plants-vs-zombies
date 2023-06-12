#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "game.h"
#include "plants.h"
using namespace std;

void Game::print_title() const
{
    cout << "|----------------|\n"
         << "|\t\tPlants vs Zombies\t\t|\n"
         << "|----------------|" << endl;
}

void Game::print_Rule() const
{
    cout << "=============================================================================\n"
         << "Plants vs. Zombies Rule:\n\n"
         << "How to win:\n"
         << "\t(1) All zombies are dead.\n"
         << "\t(2) At least one plant is live.\n"
         << "\t(3) The number of dead bomb plants cannot exceed the number of zombies.\n\n"
         << "How to lose:\n"
         << "\tAll plants are dead.\n"
         << "=============================================================================" << endl;
}

int Game::init_plants(const std::string fileName)
{
    ifstream ifs;
    ifs.open(fileName);
    if(!ifs.is_open()){
        std::cerr << "Error: cannot open file " << fileName << std::endl;
        return 0;
    }

    while (!ifs.eof()) {
        string type = 0, name, Sprice;
        int hp = 0;
        ifs >> type >> name >> Sprice >> hp;
        Sprice.erase(0, 1);
        int price = stoi(Sprice);

        ++default_choice_;
        if(type == "C"){
            int round = 0, money = 0;
            ifs >> round >> money;
            CoinPlant::set_info(name, hp, price);
            CoinPlant::set_each_round(round);
            CoinPlant::set_earn_money(money);
        } else if(type == "S"){
            int atk = 0;
            ifs >> atk;
            HornPlant::set_info(name, hp, price);
            HornPlant::set_atk(atk);
        } else if(type == "B"){
            int atk = 0;
            BombPlant::set_info(name, hp, price);
            BombPlant::set_atk(atk);
        } else if(type == "H"){
            int heal = 0;
            ifs >> heal;
            HealPlant::set_info(name, hp, price);
            HealPlant::set_heal_point(heal);
        } else {
            cout << "general plants: (class)plants" << endl;
        }
        plants_.insert({default_choice_, name});
    }
    choice_ = default_choice_;
    ifs.close();
    return 1;
}

int random_number(const int x)
{
    int random = rand() % x - x/2;
    if(random >= 0)  random += 1;
    return random;
}

void Game::player_move(Player &player)
{
    constexpr int player_move_range = 6*2;
    // get random number
    random_number(player_move_range);
    // move player
    int x = 0;
    // int x = (player.position() + random) % map.size();
    player.move_to(x);
}

void Game::zombie_action(Zombie &zombie)
{
    constexpr int zombie_move_range = 3*2;
    // get random number
    random_number(zombie_move_range);
    
    int x = 0;
    // int x = (zombie.position() + random) % map.size();
    
    zombie.move_to(x);
    // if( meet_plant )
    // {
    //     attack();
    // }
}

void Game::print_choice_option() const
{
    for(int choice = 0; choice < plants_.size(); ++choice)
    {
        cout << "[" << choice << "] " ;
        if( plants_[choice] == "Mushroom" ){
            CoinPlant::print_intro();
        } else if( plants_[choice] == "Hornflower" ){
            HealPlant::print_intro();
        } else if( plants_[choice] == "Bombflower" ){
            BombPlant::print_intro();
        } else if( plants_[choice] == "Healflower" ){
            HealPlant::print_intro();
        } else {
            cout << "general plants: (class)plants" << endl;
        }
    }
}

void Game::print_player_money(const Player &player) const
{
    cout << "Player $" << player.money() << ": " ;
    cout << "Enter your choice (" << plants_.size() << "to  give up, default: " << choice_ << ")...> ";
}

void Game::init_all_location(){
    // init zombie location
    // init player location
}

void Game::player_Choice()
{
    cin >> choice_;
    if(choice_ < 0 || choice_ > plants_.size()){
        choice_ = default_choice_;
    }
    default_choice_ = choice_;

    for(int choice = 0; choice < plants_.size(); ++choice)
    {
        cout << "[" << choice << "] " ;
        if( plants_[choice] == "Mushroom" ){

        } else if( plants_[choice] == "Hornflower" ){

        } else if( plants_[choice] == "Bombflower" ){

        } else if( plants_[choice] == "Healflower" ){

        }
    }
}

void Game::print_map(const Map &map) const
{

}

void Game::print_zombieInfo(const Zobmie &zombie) const
{

}

int Game::game_round()
{
    // Print_map();
    // Print_zombieInfo();
    // Print_player_money();
    // Print_choice_option();
    // if(play.money() >= 50){
        // Player_Choice();
    // } else {
        // cout << "You do not have enough money to plant anything!" << endl;
    // }
    // if(win_or_lose()){
    //     return 1;
    // }
    // for(){
        // Zombie_action();
        // if(win_or_lose()){
        //     return 1;
        // }
    // }
    return win_or_lose();
}

int Game::win_or_lose() const
{

    return 1;
}
