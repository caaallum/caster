#ifndef __MAP_H
#define __MAP_H

#include "vector2.h"
#include <vector>

class Map {
public:
    Map(std::vector<std::vector<int>> map);
    
    void draw();

private:
    Vector2<double> pos;
    Vector2<double> dir;
    Vector2<double> plane;
    std::vector<std::vector<int>> map;
};

#endif /* __MAP_H */
