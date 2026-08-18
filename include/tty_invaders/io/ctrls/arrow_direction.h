#ifndef TTY_INVADERS_IO_CTRLS_ARROW_DIRECTION_H
#define TTY_INVADERS_IO_CTRLS_ARROW_DIRECTION_H

#include <cstdint>

namespace tty_invaders::io::ctrls {
enum class ArrowDirection : uint16_t {
  Up = 1000,
  Down = 1001,
  Right = 1002,
  Left = 1003,
};
} // namespace tty_invaders::io::ctrls
#endif // TTY_INVADERS_IO_CTRLS_ARROW_DIRECTION_H
