#ifndef LAND_H_INCLUDED
#define LAND_H_INCLUDED

#include <iostream>
#include "plants.h"

class Plants;

class Land
{
private:
    Plants *plants_;

public:
    Land(/* args */);
    ~Land();

    const Plants *plants() const;
    Plants *plants();
    bool set_plants(Plants *);

    friend std::ostream &operator<<(std::ostream &, const Land &);
};

#endif
