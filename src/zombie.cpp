#include "zombie.h"
#include <chrono>
#include <random>

Zombie::Zombie(int hp, int attack, int max_velocity) : hp_(hp), attack_(attack), max_velocity_(max_velocity), position_(0)
{
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    this->generator = std::mt19937(seed);
    this->dist = std::uniform_int_distribution<int>(1, this->max_velocity_);
}

int Zombie::position() const
{
    return this->position_;
}

int Zombie::velocity()
{
    return this->dist(this->generator);
}

void Zombie::move_to(int pos)
{
    this->position_ = pos;
}

int Zombie::hp() const
{
    return this->hp_;
}

void Zombie::hurt(int amount)
{
    this->hp_ -= amount;
}

int Zombie::attack() const
{
    return this->attack_;
}
