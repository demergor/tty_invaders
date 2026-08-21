#include "tty_invaders/entities/templates/projectiles.h"

namespace tty_invaders::entities::templates {
const ProjectileBody bullet {
  .points {{0, 0}}, //
  .tl {0, 0},
  .br {0, 0}
};

const ProjectileBody power_up {
  .points {
    {0, 0}, //
    {-1, 1},
    {0, 1},
    {1, 1},
    {0, 2}
  },
  .tl {-1, 0},
  .br {1, 2}
};

const ProjectileBody rocket {
  .points {
    {-1, 0}, //
    {0, 0},
    {1, 0},
    {-1, 1},
    {0, 1},
    {1, 1},
    {1, 2},
    {-1, 3},
    {0, 3},
    {1, 3}
  },
  .tl {-1, 0},
  .br {1, 3}
};
} // namespace tty_invaders::entities::templates
