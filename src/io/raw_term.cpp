#include "tty_invaders/io/raw_term.h"

#include <unistd.h>

#include <iostream>

#include "tty_invaders/io/term.h"

#include <termios.h>

namespace tty_invaders::io {
RawTerm::RawTerm() {
  tcgetattr(STDIN_FILENO, &og_termios);
  termios raw {og_termios};

  raw.c_lflag &= ~static_cast<tcflag_t>(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &raw);

  std::cout << term::hide_cursor << term::enter_alternate_screen;
}

RawTerm::~RawTerm() {
  tcsetattr(STDIN_FILENO, TCSANOW, &og_termios);
  std::cout << term::show_cursor << term::leave_alternate_screen;
}
} // namespace tty_invaders::io
