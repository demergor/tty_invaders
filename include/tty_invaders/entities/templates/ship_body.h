#ifndef TTY_INVADERS_ENTITIES_TEMPLATES_SHIP_BODY_H
#define TTY_INVADERS_ENTITIES_TEMPLATES_SHIP_BODY_H

#include <cstddef>
#include <vector>

#include "tty_invaders/geometry/point.h"

namespace tty_invaders::entities::templates {
struct ShipBody {
  const std::vector<geometry::Point> hitbox_pos;
  const std::vector<std::size_t> cannon_pos;
  const int br_x;
  const int br_y;
};
} // namespace tty_invaders::entities::templates

#endif // TTY_INVADERS_ENTITIES_TEMPLATES_SHIP_BODY_H
