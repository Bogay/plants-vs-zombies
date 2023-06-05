#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

class Player
{
private:
    /* data */
public:
    Player(int money_, int max_velocity_);
    ~Player();

    int position() const;
    int velocity();
    void move_to(int);

    int money() const;
    bool spend(int);
};

#endif
