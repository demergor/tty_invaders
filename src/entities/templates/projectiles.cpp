#include "tty_invaders/entities/templates/projectile_body.h"

namespace tty_invaders::entities::templates {
const ProjectileBody bullet {
  .points {{0, 0}}, //
  .br_x = 0,
  .br_y = 0,
  .x_offset = 0
};

const ProjectileBody power_up {
  .points {
    {1, 0}, //
    {0, 1},
    {1, 1},
    {2, 1},
    {1, 2}
  },
  .br_x = 2,
  .br_y = 2,
  .x_offset = 1
};

const ProjectileBody rocket {
  .points {
    {0, 0}, //
    {1, 0},
    {2, 0},
    {0, 1},
    {1, 1},
    {2, 1},
    {2, 2},
    {0, 3},
    {1, 3},
    {2, 3}
  },
  .br_x = 2,
  .br_y = 3,
  .x_offset = 1
};
} // namespace tty_invaders::entities::templates
