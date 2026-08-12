#ifndef TTY_INVADERS_ENTITIES_PROJECTILE_BODY_H
#define TTY_INVADERS_ENTITIES_PROJECTILE_BODY_H

#include <vector>

#include "tty_invaders/geometry/point.h"

namespace tty_invaders::entities::templates {
struct ProjectileBody {
  const std::vector<geometry::Point> points;
  const int br_x;
  const int br_y;
  const int x_offset;
};
} // namespace tty_invaders::entities::templates

#endif // TTY_INVADERS_ENTITIES_PROJECTILE_BODY_H
