#include "tty_invaders/gameplay/templates/formations.h"

#include "tty_invaders/geometry/point.h"

namespace tty_invaders::gameplay::templates {
const std::vector<geometry::Point> triangle {
  {-80, 0},
  {-70, 0},
  {-60, 0},
  {-50, 0},
  {-40, 0},
  {-30, 0},
  {-20, 0},
  {-10, 0},
  {0, 0},

  {-70, 10},
  {-60, 10},
  {-50, 10},
  {-40, 10},
  {-30, 10},
  {-20, 10},
  {-10, 10},

  {-60, 20},
  {-50, 20},
  {-40, 20},
  {-30, 20},
  {-20, 20},

  {-50, 30},
  {-40, 30},
  {-30, 30},

  {-40, 40},
};

const std::vector<geometry::Point> block {
  {-40, 0},
  {-30, 0},
  {-20, 0},
  {-10, 0},
  {0, 0},

  {-40, 10},
  {-30, 10},
  {-20, 10},
  {-10, 10},
  {0, 10},

  {-40, 20},
  {-30, 20},
  {-20, 20},
  {-10, 20},
  {0, 20},

  {-40, 30},
  {-30, 30},
  {-20, 30},
  {-10, 30},
  {0, 30},

  {-40, 40},
  {-30, 40},
  {-20, 40},
  {-10, 40},
  {0, 40},
};
} // namespace tty_invaders::gameplay::templates
