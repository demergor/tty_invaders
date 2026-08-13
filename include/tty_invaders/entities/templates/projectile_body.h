#ifndef TTY_INVADERS_ENTITIES_PROJECTILE_BODY_H
#define TTY_INVADERS_ENTITIES_PROJECTILE_BODY_H

#include <vector>

#include "tty_invaders/geometry/point.h"

namespace tty_invaders::entities::templates {
struct ProjectileBody {
  const std::vector<geometry::Point> points;
  const geometry::Point tl;
  const geometry::Point br;
};
} // namespace tty_invaders::entities::templates

#endif // TTY_INVADERS_ENTITIES_PROJECTILE_BODY_H
