#ifndef LAND_H_INCLUDED
#define LAND_H_INCLUDED

#include <iostream>

class Land
{
private:
    /* data */
public:
    Land(/* args */);
    ~Land();

    friend std::ostream &operator<<(std::ostream &, const Land &);
};

#endif
