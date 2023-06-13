#include <iostream>
#include <fstream>
#include "game.h"
using namespace std;

enum
{
    CONTINUE,
    WIN,
    LOSE,
    LACKMONEY
};
enum
{
    NOTHING,
    TOOMANYBOMB
};

int parse_input(string &str)
{
    int num = 0;
    try
    {
        num = std::stoi(str);
    }
    catch (const std::invalid_argument &e)
    {
        num = -1;
    }
    return num;
}

Game::Game(string num_land, string num_zombie)
{
    num_land_ = parse_input(num_land);
    num_zombie_ = parse_input(num_zombie);
    if (num_land_ < 1 || num_land_ > max_num_land)
    {
        num_land_ = default_num_land;
    }
    if (num_zombie_ < 1 || num_zombie_ > max_num_zombie)
    {
        num_zombie_ = default_num_zombie;
    }

    num_land_ = parse_input(num_land);
    num_zombie_ = parse_input(num_zombie);
    cur_zombie_num_ = num_zombie_;
    map_ = new Map(num_land_);
    player_ = new Player(default_money, player_v);
    all_zombies_ = std::vector<Zombie *>(num_zombie_);
    all_plants_ = std::vector<Plants *>();
    for (int i = 0; i < num_zombie_; ++i)
    {
        all_zombies_[i] = new Zombie(zombie_hp, zombie_atk, zombie_v);
    }
}

void Game::print_title()
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

int Game::init_plants_setting(const std::string fileName)
{
    ifstream ifs;
    ifs.open(fileName);
    if (!ifs.is_open())
    {
        std::cerr << "Error: cannot open file " << fileName << std::endl;
        return 0;
    }

    while (!ifs.eof())
    {
        string type, name, Sprice;
        int hp = 0;
        ifs >> type >> name >> Sprice >> hp;
        Sprice.erase(0, 1);
        std::cerr << ' ' << type << ' ' << name << ' ' << Sprice << ' ' << hp << '\n';
        int price = stoi(Sprice);
        if (price <= lowest_price_)
            lowest_price_ = price;

        if (type == "C")
        {
            int round = 0, money = 0;
            ifs >> round >> money;
            CoinPlant::set_info(name, hp, price);
            CoinPlant::set_each_round(round);
            CoinPlant::set_earn_money(money);
        }
        else if (type == "S")
        {
            int atk = 0;
            ifs >> atk;
            HornPlant::set_info(name, hp, price);
            HornPlant::set_atk(atk);
        }
        else if (type == "B")
        {
            int atk = 0;
            BombPlant::set_info(name, hp, price);
            BombPlant::set_atk(atk);
        }
        else if (type == "H")
        {
            int heal = 0;
            ifs >> heal;
            HealPlant::set_info(name, hp, price);
            HealPlant::set_heal_point(heal);
        }
        ++default_choice_;
        plants_map_.insert({default_choice_, name});
    }
    choice_ = default_choice_;
    ifs.close();
    return 1;
}

void Game::player_move()
{
    int x = (player_->velocity() + player_->position()) % num_land_;
    player_->move_to(x);
}

int Game::zombie_action(vector<Zombie *> &zombies)
{
    for (int i = 0; i < num_zombie_; ++i)
    {
        if (all_zombies_[i] == nullptr)
        {
            continue;
        }
        int x = (zombies[i]->velocity() + zombies[i]->position()) % num_land_;
        zombies[i]->move_to(x);
        cout << "Zombie [" << i << "] moves to land " << x << "." << endl;
        Plants *plant = map_->plants(x);
        if (plant != nullptr)
        {
            if (plant->get_name() == BombPlant::get_info().get_name())
            {
                if (num_bombPlant_ * 2 > num_zombie_)
                {
                    cout << "You lose the game since you cannot use that many bomb plants!" << endl;
                    return TOOMANYBOMB;
                }
                --num_bombPlant_;
            }
            if (plant->zombie_visit(*zombies[i]))
            {
                delete map_->plants(x);
                map_->set_plants(zombies[i]->position(), nullptr);
                all_plants_.erase(all_plants_.begin() + x);
                --num_plant_;
            }
            if (zombies[i]->hp() <= 0)
            {
                delete zombies[i];
                zombies[i] = nullptr;
                --cur_zombie_num_;
            }
        }
    }

    return NOTHING;
}

void Game::print_choice_option() const
{
    for (int choice = 0; choice < plants_map_.size(); ++choice)
    {
        cout << "[" << choice << "] ";
        if (plants_map_[choice] == "Mushroom")
        {
            CoinPlant::print_intro();
        }
        else if (plants_map_[choice] == "Hornflower")
        {
            HealPlant::print_intro();
        }
        else if (plants_map_[choice] == "Bombflower")
        {
            BombPlant::print_intro();
        }
        else if (plants_map_[choice] == "Healflower")
        {
            HealPlant::print_intro();
        }
        else
        {
            cout << "general plants: (class)plants" << endl;
        }
    }
}

void Game::print_player_money() const
{
    cout << "Player $" << player_->money() << ": \t"
         << "Enter your choice (" << plants_map_.size()
         << "to  give up, default: " << choice_ << ")...> ";
}

// TODO: init rules?
void Game::init_all_location()
{
    for (int i = 0; i < num_zombie_; ++i)
    {
        int x = rand() % num_land_;
        all_zombies_[i]->move_to(x);
    }

    int x = rand() % num_land_;
    player_->move_to(x);
}

int Game::player_Choice()
{
    string input = "";
    cin >> input;
    choice_ = parse_input(input);
    if (choice_ < 0 || choice_ > plants_map_.size())
    {
        choice_ = default_choice_;
    }
    default_choice_ = choice_;

    if (choice_ == plants_map_.size())
    {
        cout << "You give up!" << endl;
        return CONTINUE;
    }

    // for (int choice = 0; choice < plants_map_.size(); ++choice)
    // {
    if (plants_map_[choice_] == CoinPlant::get_info().get_name())
    {
        if (player_->money() < CoinPlant::get_info().get_price())
        {
            cout << "Not enough money! Please input again!" << endl;
            return LACKMONEY;
        }
        player_->spend(CoinPlant::get_info().get_price());
        CoinPlant *coin_plant = new CoinPlant();
        all_plants_.push_back(coin_plant);
        map_->set_plants(player_->position(), coin_plant);
        cout << "You have planted " << CoinPlant::get_info().get_name()
             << " at land " << player_->position() << " !" << endl;
    }
    else if (plants_map_[choice_] == HornPlant::get_info().get_name())
    {
        if (player_->money() < HornPlant::get_info().get_price())
        {
            cout << "Not enough money! Please input again!" << endl;
            return LACKMONEY;
        }

        player_->spend(HornPlant::get_info().get_price());
        HornPlant *horn_plant = new HornPlant();
        all_plants_.push_back(horn_plant);
        map_->set_plants(player_->position(), horn_plant);
        cout << "You have planted " << HornPlant::get_info().get_name()
             << " at land " << player_->position() << " !" << endl;
    }
    else if (plants_map_[choice_] == BombPlant::get_info().get_name())
    {
        if (player_->money() < BombPlant::get_info().get_price())
        {
            cout << "Not enough money! Please input again!" << endl;
            return LACKMONEY;
        }

        player_->spend(BombPlant::get_info().get_price());
        BombPlant *bomb_plant = new BombPlant();
        map_->set_plants(player_->position(), bomb_plant);
        all_plants_.push_back(bomb_plant);
        ++num_bombPlant_;
        cout << "You have planted " << BombPlant::get_info().get_name()
             << " at land " << player_->position() << " !" << endl;
    }
    else if (plants_map_[choice_] == HealPlant::get_info().get_name())
    {
        if (player_->money() < HealPlant::get_info().get_price())
        {
            cout << "Not enough money! Please input again!" << endl;
            return LACKMONEY;
        }

        player_->spend(HealPlant::get_info().get_price());
        HealPlant *heal_plant = new HealPlant();
        map_->set_plants(player_->position(), heal_plant);
        all_plants_.push_back(heal_plant);
        cout << "You have planted " << HealPlant::get_info().get_name()
             << " at land " << player_->position() << " !" << endl;
    }
    // }
    ++num_plant_;
    return CONTINUE;
}

void Game::print_map() const
{
    for (int i = 0; i < map_->size(); i++)
    {
        cout << "[" << i << "]{ ";
        if (player_->position() == i)
            cout << "*";
        else
            cout << " ";

        for (int j = 0; j < num_zombie_; ++j)
        {
            if (all_zombies_[j] == nullptr)
                cout << " ";
            if (all_zombies_[j]->position() == i)
                cout << j;
            else
                cout << " ";
        }

        cout << "}";

        if (map_->plants(i) == nullptr)
            cout << "Empty" << endl;
        else
        {
            cout << *map_->plants(i);
        }
    }
}

void Game::print_zombieInfo() const
{
    cout << "Zombie information:" << endl;
    for (int i = 0; i < num_zombie_; ++i)
    {
        if (all_zombies_[i] == nullptr)
        {
            continue;
        }
        cout << "[" << i << "] Damage: " << all_zombies_[i]->attack() << "HP:";
        for (int j = 0; j < all_zombies_[i]->hp(); ++j)
        {
            cout << "*";
        }
        cout << endl;
    }
}

void Game::visit_plant(Plants *plant)
{
    string name = plant->get_name();
    plant->player_visit(*player_);
}

int Game::game_round()
{

#if defined _WIN32
    system("cls");
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined(__APPLE__)
    system("clear");
#endif

    print_map();
    cout << "------------------------------------------------" << endl;
    print_zombieInfo();
    cout << "================================================" << endl;

    Plants *plant_in_land = map_->plants(player_->position());
    if (player_->money() >= lowest_price_ && plant_in_land == nullptr)
    {
        print_choice_option();
        cout << endl;
        print_player_money();
        if (LACKMONEY == player_Choice())
        {
            return CONTINUE;
        }
    }
    else if (plant_in_land != nullptr)
    {
        visit_plant(map_->plants(player_->position()));
    }
    else
    {
        cout << "You do not have enough money to plant anything!" << endl;
    }
    if (win_or_lose())
    {
        return !CONTINUE;
    }
    if (zombie_action(all_zombies_) == TOOMANYBOMB)
    {
        return LOSE;
    }

    player_move();
    return win_or_lose();
}

int Game::win_or_lose() const
{
    if (cur_zombie_num_ == 0 && num_plant_ > 0)
    {
        cout << "Congratulation! You have killed all zombies!" << endl;
        return WIN;
    }

    if (num_plant_ == 0)
    {
        cout << "Oh no... You have no plant on the map ...." << endl;
        return LOSE;
    }

    return CONTINUE;
}

vector<Plants *> Game::all_plants() const
{
    return all_plants_;
}
