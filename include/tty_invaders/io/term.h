#ifndef TTY_INVADERS_IO_TERM_H
#define TTY_INVADERS_IO_TERM_H

#include <cstddef>
#include <format>
#include <iterator>
#include <string>
#include <string_view>

namespace tty_invaders::io::term {
// Control
constexpr std::string_view clear_screen {"\033[2J"}; // Clears visible screen
constexpr std::string_view clear_line {"\033[2K"};   // Clears current line
constexpr std::string_view hide_cursor {"\033[?25l"};
constexpr std::string_view show_cursor {"\033[?25h"};
constexpr std::string_view enter_alternate_screen {"\033[?1049h"};
constexpr std::string_view leave_alternate_screen {"\033[?1049l"};
constexpr std::string_view reset {"\033[0m"};

// Navigation
constexpr std::string_view cursor_home {"\033[H"}; // Moves cursor to (0,0)
constexpr std::string_view cursor_up {"\033[A"};
constexpr std::string_view cursor_down {"\033[B"};
constexpr std::string_view cursor_right {"\033[C"};
constexpr std::string_view cursor_left {"\033[D"};

// Styles
constexpr std::string_view bold {"\033[1m"};
constexpr std::string_view dim {"\033[2m"};
constexpr std::string_view underline {"\033[4m"};

// Foreground (Text) Colors
constexpr std::string_view grey {"\033[90m"};
constexpr std::string_view red {"\033[31m"};
constexpr std::string_view black {"\033[30m"};
constexpr std::string_view green {"\033[32m"};
constexpr std::string_view yellow {"\033[33m"};
constexpr std::string_view blue {"\033[34m"};
constexpr std::string_view magenta {"\033[35m"};
constexpr std::string_view cyan {"\033[36m"};
constexpr std::string_view white {"\033[37m"};

// Bright Foreground Colors
constexpr std::string_view bright_red {"\033[91m"};
constexpr std::string_view bright_green {"\033[92m"};
constexpr std::string_view bright_yellow {"\033[93m"};
constexpr std::string_view bright_blue {"\033[94m"};

// Background Colors
constexpr std::string_view bg_red {"\033[41m"};
constexpr std::string_view bg_green {"\033[42m"};
constexpr std::string_view bg_yellow {"\033[43m"};
constexpr std::string_view bg_blue {"\033[44m"};

inline std::string cursor_down_n(std::size_t n) {
  return std::format("\033[{}B", n);
}

inline void move_cursor(
  std::string& out_buf,
  const std::size_t x,
  const std::size_t y
) {
  std::format_to(std::back_inserter(out_buf), "\033[{};{}H", y + 1, x + 1);
}
} // namespace tty_invaders::io::term

#endif // TTY_INVADERS_IO_TERM_H
