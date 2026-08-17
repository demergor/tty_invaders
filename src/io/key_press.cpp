#include "tty_invaders/io/key_press.h"

#include <utility>

namespace tty_invaders::io {
bool KeyPress::operator==(const KeyPress& other) {
  if (type != other.type) {
    return false;
  }

  switch (type) {
    case Type::None: return true;
    case Type::Arrow: return arrow == other.arrow;
    case Type::Char: return ch == other.ch;
    default: std::unreachable();
  }
}
} // namespace tty_invaders::io
