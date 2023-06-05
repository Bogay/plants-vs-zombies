#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <iostream>

class Map
{
private:
    /* data */
public:
    Map(/* Game&, */ int size);
    ~Map();

    void update();

    friend std::ostream &operator<<(std::ostream &, const Map &);
};

#endif
