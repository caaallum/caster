#ifndef __MAP_H
#define __MAP_H

#include "vector2.h"
#include <vector>

class Map {
public:
    Map(std::vector<std::vector<int>> map);
    explicit Map() {}
    void draw();

    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();

private:
    Vector2<double> m_pos;
    Vector2<double> m_dir;
    Vector2<double> m_plane;
    std::vector<std::vector<int>> m_map;
    double m_time;
    double m_old_time;
    double m_move_speed;
    double m_rot_speed;
};

#endif /* __MAP_H */
