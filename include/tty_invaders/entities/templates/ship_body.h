#ifndef TTY_INVADERS_ENTITIES_TEMPLATES_SHIP_BODY_H
#define TTY_INVADERS_ENTITIES_TEMPLATES_SHIP_BODY_H

#include <cstddef>
#include <vector>

namespace tty_invaders::entities::templates {
struct ShipBody {
  struct Point {
    int x;
    int y;
  };

  std::vector<ShipBody::Point> hitbox_pos;
  std::vector<std::size_t> cannon_pos;
};
} // namespace tty_invaders::entities::templates

#endif // TTY_INVADERS_ENTITIES_TEMPLATES_SHIP_BODY_H
