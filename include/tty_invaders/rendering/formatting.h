#ifndef TTY_INVADERS_RENDERING_FORMATTING_H
#define TTY_INVADERS_RENDERING_FORMATTING_H

#include <array>
#include <cstdint>
#include <string>
#include <utility>

#include "tty_invaders/io/term.h"

namespace tty_invaders::rendering {
enum class Formatting : uint32_t {
  None = 0u,
  Bold = 1u << 0,
  Dim = 1u << 1,
  Underline = 1u << 2,

  Black = 1u << 3,
  Red = 1u << 4,
  Green = 1u << 5,
  Yellow = 1u << 6,
  Blue = 1u << 7,
  White = 1u << 8,
  Grey = 1u << 9,

  BrightRed = 1u << 10,
  BrightGreen = 1u << 11,
  BrightYellow = 1u << 12,
  BrightBlue = 1u << 13,

  BgRed = 1u << 14,
  BgGreen = 1u << 15,
  BgYellow = 1u << 16,
  BgBlue = 1u << 17,
};

constexpr std::array formatting_codes {
  std::pair {Formatting::Bold, io::term::bold},
  std::pair {Formatting::Dim, io::term::dim},
  std::pair {Formatting::Underline, io::term::underline},

  std::pair {Formatting::Black, io::term::black},
  std::pair {Formatting::Red, io::term::red},
  std::pair {Formatting::Green, io::term::green},
  std::pair {Formatting::Yellow, io::term::yellow},
  std::pair {Formatting::Blue, io::term::blue},
  std::pair {Formatting::White, io::term::white},
  std::pair {Formatting::Grey, io::term::grey},

  std::pair {Formatting::BrightRed, io::term::bright_red},
  std::pair {Formatting::BrightGreen, io::term::bright_green},
  std::pair {Formatting::BrightYellow, io::term::bright_yellow},
  std::pair {Formatting::BrightBlue, io::term::bright_blue},

  std::pair {Formatting::BgRed, io::term::bg_red},
  std::pair {Formatting::BgGreen, io::term::bg_green},
  std::pair {Formatting::BgYellow, io::term::bg_yellow},
  std::pair {Formatting::BgBlue, io::term::bg_blue},
};

inline constexpr bool operator==(Formatting lop, Formatting rop) {
  return std::to_underlying(lop) == std::to_underlying(rop);
}

inline constexpr bool operator!=(Formatting lop, Formatting rop) {
  return !(lop == rop);
}

inline constexpr Formatting operator|(Formatting lop, Formatting rop) {
  return static_cast<Formatting>(std::to_underlying(lop) | std::to_underlying(rop));
}

inline constexpr Formatting operator&(Formatting lop, Formatting rop) {
  return static_cast<Formatting>(std::to_underlying(lop) & std::to_underlying(rop));
}

inline constexpr Formatting operator^(Formatting lop, Formatting rop) {
  return static_cast<Formatting>(std::to_underlying(lop) ^ std::to_underlying(rop));
}

inline constexpr Formatting& operator|=(Formatting& lop, Formatting rop) {
  return lop = lop | rop;
}

inline constexpr Formatting& operator&=(Formatting& lop, Formatting rop) {
  return lop = lop & rop;
}

inline constexpr Formatting& operator^=(Formatting& lop, Formatting rop) {
  return lop = lop ^ rop;
}

inline constexpr bool is_subset(Formatting subset, Formatting superset) {
  return (superset & subset) == subset;
}

inline constexpr std::string to_string(Formatting formatting) {
  if (formatting == Formatting::None) {
    return "";
  }

  std::string result;
  for (const auto& [format, code] : formatting_codes) {
    result += (formatting & format) == Formatting::None ? "" : code;
  }

  return result;
}

inline std::string ansi_escape(const Formatting& prev, const Formatting& cur) {
  std::string result;
  if (!is_subset(prev, cur)) {
    result = io::term::reset;
    return result + to_string(cur);
  }

  return to_string(cur ^ prev);
}
} // namespace tty_invaders::rendering

#endif // TTY_INVADERS_RENDERING_FORMATTING_H
