#include "map.h"
#include "game.h"
#include <glm/glm.hpp>
#include "line.h"

extern Game game;

Map::Map(std::vector<std::vector<int>> map) :
    m_map(map),
    m_pos(22, 12),
    m_dir(-1, 0),
    m_plane(0, 0.66) {
    
}

void
Map::draw() {
     for (int x = 0; x < game.width; x++) {
      double camera = 2 * x / (double)game.width - 1;
      Vector2<double> ray_dir = {m_dir.x + m_plane.x * camera,
                                 m_dir.y + m_plane.y * camera};

      Vector2<int> map = {(int)m_pos.x, (int)m_pos.y};
      Vector2<double> side_dist = {0, 0};

      Vector2<double> delta_dist = {
          (ray_dir.x == 0) ? 1e30 : fabs(1 / ray_dir.x),
          (ray_dir.y == 0) ? 1e30 : fabs(1 / ray_dir.y)};
      double perp_wall_dist;

      Vector2<int> step;

      int hit = 0;
      int side;

      if (ray_dir.x < 0) {
        step.x = -1;
        side_dist.x = (m_pos.x - map.x) * delta_dist.x;
      } else {
        step.x = 1;
        side_dist.x = (map.x + 1.0 - m_pos.x) * delta_dist.x;
      }
      if (ray_dir.y < 0) {
        step.y = -1;
        side_dist.y = (m_pos.y - map.y) * delta_dist.y;
      } else {
        step.y = 1;
        side_dist.y = (map.y + 1.0 - m_pos.y) * delta_dist.y;
      }

      while (hit == 0) {
        if (side_dist.x < side_dist.y) {
          side_dist.x += delta_dist.x;
          map.x += step.x;
          side = 0;
        } else {
          side_dist.y += delta_dist.y;
          map.y += step.y;
          side = 1;
        }
        if (m_map[map.x][map.y] > 0)
          hit = 1;
      }

      if (side == 0) {
        perp_wall_dist = (side_dist.x - delta_dist.x);
      } else {
        perp_wall_dist = (side_dist.y - delta_dist.y);
      }

      int line_height = (int)(game.height / perp_wall_dist);

      int draw_start = -line_height / 2 + game.height / 2;
      if (draw_start < 0) {
        draw_start = 0;
      }
      int draw_end = line_height / 2 + game.height / 2;
      if (draw_end >= game.height) {
        draw_end = game.height - 1;
      }
        glm::vec3 color(0);
        switch(m_map[map.x][map.y]) {
            case 1: color.x = 1; break; // Red
            case 2: color.y = 1; break; // Green
            case 3: color.z = 1; break; // Blue
            case 4: color.x = 1; color.y = 1; color.z = 1; break;
            default: color.x = 1; color.y = 1; break;
        }
        if (side == 1) {
            color.x /= 2;
            color.y /= 2;
            color.z /= 2;
        }
        line_draw({x, draw_start}, {x, draw_end}, color);
    }
}