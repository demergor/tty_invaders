#ifndef TTY_INVADERS_ENTITIES_PROJECTILE_BODY_H
#define TTY_INVADERS_ENTITIES_PROJECTILE_BODY_H

#include <vector>

#include "tty_invaders/geometry/coord.h"

namespace tty_invaders::entities {
  struct ProjectileBody {
    const std::vector<geometry::Coord> coords;
    const int br_x;
    const int br_y;
  };
}

#endif // TTY_INVADERS_ENTITIES_PROJECTILE_BODY_H
