#ifndef TTY_INVADERS_RENDERING_FORMATTING_H
#define TTY_INVADERS_RENDERING_FORMATTING_H

#include <cstdint>
#include <utility>

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
} // namespace tty_invaders::rendering

#endif // TTY_INVADERS_RENDERING_FORMATTING_H
