#ifndef __MAP_H
#define __MAP_H

#include "vector2.h"
#include <vector>

class Map {
public:
    Map(std::vector<std::vector<int>> map);
    explicit Map() {}
    void draw();

private:
    Vector2<double> m_pos;
    Vector2<double> m_dir;
    Vector2<double> m_plane;
    std::vector<std::vector<int>> m_map;
};

#endif /* __MAP_H */
