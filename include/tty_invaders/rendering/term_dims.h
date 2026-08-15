#ifndef TTY_INVADERS_RENDERING_TERM_DIMS_H
#define TTY_INVADERS_RENDERING_TERM_DIMS_H

#include <cstddef>

namespace tty_invaders::rendering {
struct TermDims {
  explicit TermDims();

  std::size_t main_height;
  std::size_t bar_height;
  std::size_t width;
};
} // namespace tty_invaders::rendering

#endif // TTY_INVADERS_RENDERING_TERM_DIMS_H
