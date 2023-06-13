#include <vector>
#include "map.h"
#include "land.h"
#include "plants.h"

Map::Map(int size)
{
    this->lands_ = std::vector<Land>(size);
}

Plants *Map::plants(int i)
{
    return this->lands_[i].plants();
}

const Plants *Map::plants(int i) const
{
    return this->lands_[i].plants();
}

bool Map::set_plants(int i, Plants *plants)
{
    return this->lands_[i].set_plants(plants);
}

int Map::size() const
{
    return this->lands_.size();
}
