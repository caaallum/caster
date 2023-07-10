#include "map.h"

Map::Map(std::vector<std::vector<int>> map) :
    map(map),
    pos(22, 12),
    dir(-1, 0),
    plane(0, 0.66) {
    
}
