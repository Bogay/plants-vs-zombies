#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <iostream>
#include <vector>
#include "land.h"
#include "plants.h"

class Land;
class Plants;

class Map
{
private:
    std::vector<Land> lands_;

public:
    Map(/* Game&, */ int size);
    ~Map();

    void update();
    Plants *plants(int i);
    const Plants *plants(int i) const;
    bool set_plants(int i, Plants *);
    int size() const;

    friend std::ostream &operator<<(std::ostream &, const Map &);
};

#endif
