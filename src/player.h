#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <random>

class Player
{
private:
    int money_;
    int max_velocity_;
    int position_;
    std::mt19937 generator;
    std::uniform_int_distribution<int> dist;

public:
    Player(int money, int max_velocity);
    ~Player();

    int position() const;
    int velocity();
    void move_to(int);

    int money() const;
    bool spend(int);
    bool earn(int);
};

#endif
