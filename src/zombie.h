#ifndef ZOMBIE_H_INCLUDED
#define ZOMBIE_H_INCLUDED

#include <random>

class Zombie
{
private:
    int hp_;
    int attack_;
    int max_velocity_;
    int position_;
    std::mt19937 generator;
    std::uniform_int_distribution<int> dist;

public:
    Zombie(int hp, int attack, int max_velocity);
    ~Zombie();

    int position() const;
    int velocity();
    void move_to(int);

    int hp() const;
    void hurt(int);
    int attack() const;
};

#endif
