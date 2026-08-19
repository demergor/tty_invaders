#ifndef TESTS_HELPERS_SETUP_HELPERS_H
#define TESTS_HELPERS_SETUP_HELPERS_H

#include <cstddef>

#include "tty_invaders/gameplay/collision_buffer.h"
#include "tty_invaders/rendering/term_dims.h"

namespace tty_invaders::tests::helpers {
inline rendering::TermDims term_dims(
  const std::size_t bar_height,
  const std::size_t main_height,
  const std::size_t width
) {
  rendering::TermDims td;
  td.main_height = main_height;
  td.bar_height = bar_height;
  td.width = width;
  return td;
}

inline gameplay::CollisionBuffer collision_buffer(
  const std::size_t height,
  const std::size_t width
) {
  rendering::TermDims td;
  td.main_height = height;
  td.width = width;

  gameplay::CollisionBuffer cb {td};

  return cb;
}
} // namespace tty_invaders::tests::helpers

#endif // TESTS_HELPERS_SETUP_HELPERS_H
