#include "tty_invaders/entities/templates/ships.h"

namespace tty_invaders::entities::templates {
const ShipBody destroyer {
  .hitbox_pos {
    {2, 0},
    {0, 1},
    {2, 1},
    {4, 1},
    {0, 2},
    {1, 2},
    {2, 2},
    {3, 2},
    {4, 2},
    {1, 3},
    {2, 3},
    {3, 3},
    {0, 4},
    {1, 4},
    {2, 4},
    {3, 4},
    {2, 5}
  },
  .cannon_pos {0, 1, 3},
  .br_x = 4,
  .br_y = 5
};

const ShipBody fighter {
  .hitbox_pos {
    {1, 0},
    {2, 0},
    {3, 0},
    {0, 1},
    {1, 1},
    {2, 1},
    {3, 1},
    {4, 1},
    {0, 2},
    {2, 2},
    {4, 2}
  },
  .cannon_pos {0, 1, 2},
  .br_x = 4,
  .br_y = 2
};

// TODO: Define (more)
/*
 * const ShipBody invader {
 * .hitbox_pos {
 * },
 * .cannon_pos {0, 1, 2},
 * .br_x
 * };
 */

const ShipBody speeder {
  .hitbox_pos {
    {1, 0}, //
    {0, 1},
    {1, 1},
    {2, 1},
    {0, 2},
    {2, 2}
  },
  .cannon_pos {0},
  .br_x = 2,
  .br_y = 2
};
} // namespace tty_invaders::entities::templates
