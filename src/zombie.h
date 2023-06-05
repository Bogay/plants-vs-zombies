#ifndef ZOMBIE_H_INCLUDED
#define ZOMBIE_H_INCLUDED

class Zombie
{
private:
    /* data */
public:
    Zombie(int hp_, int attack_, int max_velocity_);
    ~Zombie();

    int position() const;
    int velocity();
    void move_to(int);

    int hp() const;
    void hurt(int);
    int attack() const;
};

#endif
