#include "land.h"

Land::Land() : plants_(NULL) {}
Land::~Land() {}

const Plants *Land::plants() const
{
    return this->plants_;
}

Plants *Land::plants()
{
    return this->plants_;
}

bool Land::set_plants(Plants *plants)
{
    if (this->plants() != NULL)
        return false;
    this->plants_ = plants;
    return true;
}
