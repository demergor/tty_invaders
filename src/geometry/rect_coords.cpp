#include "tty_invaders/geometry/rect_coords.h"

namespace tty_invaders::geometry {
bool RectCoords::empty() const {
  return tl_x >= br_x || tl_y >= br_y;
}
} // namespace tty_invaders::geometry
