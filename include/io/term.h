#ifndef TTY_INVADERS_IO_TERM_H
#define TTY_INVADERS_IO_TERM_H

#include <cstddef>
#include <format>
#include <iterator>
#include <string_view>

namespace tty_invaders::io::term {
// Control
inline constexpr std::string_view clear_screen {"\033[2J"}; // Clears visible screen
inline constexpr std::string_view clear_line {"\033[2K"};   // Clears current line
inline constexpr std::string_view cursor_home {"\033[H"};   // Moves cursor to (0,0)
inline constexpr std::string_view hide_cursor {"\033[?25l"};
inline constexpr std::string_view show_cursor {"\033[?25h"};
inline constexpr std::string_view enter_alternate_screen {"\033[?1049h"};
inline constexpr std::string_view leave_alternate_screen {"\033[?1049l"};
inline constexpr std::string_view reset {"\033[0m"};

// Styles
inline constexpr std::string_view bold {"\033[1m"};
inline constexpr std::string_view underline {"\033[4m"};

// Foreground (Text) Colors
inline constexpr std::string_view red {"\033[31m"};
inline constexpr std::string_view green {"\033[32m"};
inline constexpr std::string_view yellow {"\033[33m"};
inline constexpr std::string_view blue {"\033[34m"};
inline constexpr std::string_view magenta {"\033[35m"};
inline constexpr std::string_view cyan {"\033[36m"};
inline constexpr std::string_view white {"\033[37m"};

// Bright Foreground Colors
inline constexpr std::string_view b_red {"\033[91m"};
inline constexpr std::string_view b_green {"\033[92m"};
inline constexpr std::string_view b_yellow {"\033[93m"};
inline constexpr std::string_view b_blue {"\033[94m"};

// Background Colors
inline constexpr std::string_view bg_red {"\033[41m"};
inline constexpr std::string_view bg_green {"\033[42m"};
inline constexpr std::string_view bg_yellow {"\033[43m"};
inline constexpr std::string_view bg_blue {"\033[44m"};

inline void move_cursor(
  std::string& out_buf, const std::size_t x, const std::size_t y
) {
  std::format_to(std::back_inserter(out_buf), "\033[{};{}H", y + 1, x + 1);
}
} // namespace tty_invaders::io::term

#endif // TTY_INVADERS_IO_TERM_H

