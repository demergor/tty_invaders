#include "tty_invaders/rendering/term_dims.h"

#include <sys/ioctl.h>
#include <unistd.h>

#include <stdexcept>

#include "tty_invaders/opts/game_settings.h"

namespace tty_invaders::rendering {
TermDims::TermDims() {
  winsize w;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w)) {
    main_height = 26;
    bar_height = 1;
    width = 80;
    return;
  }

  bar_height = opts::game_settings::action_bar_height;
  if (bar_height > w.ws_row) {
    throw std::runtime_error("Action bar height too big for available terminal size!");
  }

  main_height = w.ws_row - bar_height;
  width = w.ws_col;
}
} // namespace tty_invaders::rendering
