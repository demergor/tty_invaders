#ifndef TTY_INVADERS_IO_RAW_TERM
#define TTY_INVADERS_IO_RAW_TERM

#include <termios.h>

namespace tty_invaders::io {
struct RawTerm {
  explicit RawTerm();

  ~RawTerm();

private:
  struct termios og_termios;
};
} // namespace tty_invaders::io

#endif
