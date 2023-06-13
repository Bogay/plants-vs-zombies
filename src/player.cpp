#include "player.h"
#include <chrono>
#include <random>

Player::Player(int money, int max_velocity) : money_(money), max_velocity_(max_velocity), position_(0)
{
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    this->generator = std::mt19937(seed);
    this->dist = std::uniform_int_distribution<int>(1, this->max_velocity_);
}

int Player::position() const
{
    return this->position_;
}

int Player::velocity()
{
    return this->dist(this->generator);
}

void Player::move_to(int pos)
{
    this->position_ = pos;
}

int Player::money() const
{
    return this->money_;
}

bool Player::spend(int amount)
{
    if (amount > this->money())
        return false;
    this->money_ -= amount;
    return true;
}

bool Player::earn(int amount)
{
    this->money_ += amount;
    return true;
}
