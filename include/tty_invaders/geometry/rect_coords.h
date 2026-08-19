#ifndef TTY_INVADERS_GEOMETRY_RECT_COORDS_H
#define TTY_INVADERS_GEOMETRY_RECT_COORDS_H

#include <cstddef>

namespace tty_invaders::geometry {
struct RectCoords {
  bool empty() const;

  std::size_t tl_x {0};
  std::size_t tl_y {0};
  std::size_t br_x {0};
  std::size_t br_y {0};
};
} // namespace tty_invaders::geometry

#endif // TTY_INVADERS_GEOMETRY_RECT_COORDS_H
