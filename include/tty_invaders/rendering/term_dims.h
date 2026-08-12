#ifndef TTY_INVADERS_RENDERING_TERM_DIMS_H
#define TTY_INVADERS_RENDERING_TERM_DIMS_H

namespace tty_invaders::rendering {
struct TermDims {
  explicit TermDims();

  int main_height;
  int bar_height;
  int width;
};
} // namespace tty_invaders::rendering

#endif // TTY_INVADERS_RENDERING_TERM_DIMS_H
