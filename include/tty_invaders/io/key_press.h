#ifndef TTY_INVADERS_IO_KEY_PRESS_H
#define TTY_INVADERS_IO_KEY_PRESS_H

#include "tty_invaders/io/ctrls/arrow_direction.h"

namespace tty_invaders::io {
struct KeyPress {
  enum class Type {
    None,
    Char,
    Arrow
  };

  bool operator==(const KeyPress&);

  Type type;
  ctrls::ArrowDirection arrow {};
  unsigned char ch {};
};
} // namespace tty_invaders::io

#endif // TTY_INVADERS_IO_KEY_PRESS_H
