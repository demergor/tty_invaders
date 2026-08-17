#include "tty_invaders/io/io.h"

#include <sys/poll.h>
#include <unistd.h>

#include <vector>

namespace tty_invaders::io {
namespace {
bool read_byte(char& out) {
  pollfd pfd {.fd = STDIN_FILENO, .events = POLLIN, .revents = 0};
  return poll(&pfd, 1, 0) > 0 && (pfd.revents & POLLIN)
    && read(STDIN_FILENO, &out, 1) == 1;
}
} // namespace

KeyPress key_pressed() {
  char ch {};
  std::vector<char> bytes;

  while (read_byte(ch)) {
    bytes.emplace_back(ch);
  }

  if (bytes.empty()) {
    return KeyPress {.type = KeyPress::Type::None};
  }

  if (
    bytes.size() < 3 || bytes[bytes.size() - 3] != '\x1b'
    || bytes[bytes.size() - 2] != '['
  ) {
    return KeyPress {
      .type = KeyPress::Type::Char,
      .ch = static_cast<unsigned char>(bytes.back())
    };
  }

  switch (bytes[bytes.size() - 1]) {
    case 'A':
      return KeyPress {
        .type = KeyPress::Type::Arrow,
        .arrow = ctrls::ArrowDirection::Up
      };
    case 'B':
      return KeyPress {
        .type = KeyPress::Type::Arrow,
        .arrow = ctrls::ArrowDirection::Down
      };
    case 'C':
      return KeyPress {
        .type = KeyPress::Type::Arrow,
        .arrow = ctrls::ArrowDirection::Right
      };
    case 'D':
      return KeyPress {
        .type = KeyPress::Type::Arrow,
        .arrow = ctrls::ArrowDirection::Left
      };
    default: return KeyPress {.type = KeyPress::Type::None};
  }
}
} // namespace tty_invaders::io
