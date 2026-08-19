#ifndef TTY_INVADERS_EFFECTS_STATUS_EFFECTS_H
#define TTY_INVADERS_EFFECTS_STATUS_EFFECTS_H

#include <utility>

namespace tty_invaders::effects {
enum class StatusEffect : int {
  None = 0u,
  DoubleAtkSpd = 1u << 0,
  DoubleDmg = 1u << 1,
  Invincible = 1u << 2,
  Homing = 1u << 3,
  Laser = 1u << 4
};

inline constexpr bool operator==(StatusEffect lop, StatusEffect rop) {
  return std::to_underlying(lop) == std::to_underlying(rop);
}

inline constexpr bool operator!=(StatusEffect lop, StatusEffect rop) {
  return !(lop == rop);
}

inline constexpr StatusEffect operator|(StatusEffect lop, StatusEffect rop) {
  return static_cast<StatusEffect>(std::to_underlying(lop) | std::to_underlying(rop));
}

inline constexpr StatusEffect operator&(StatusEffect lop, StatusEffect rop) {
  return static_cast<StatusEffect>(std::to_underlying(lop) & std::to_underlying(rop));
}

inline constexpr StatusEffect operator^(StatusEffect lop, StatusEffect rop) {
  return static_cast<StatusEffect>(std::to_underlying(lop) ^ std::to_underlying(rop));
}

inline constexpr StatusEffect& operator|=(StatusEffect& lop, StatusEffect rop) {
  return lop = lop | rop;
}

inline constexpr StatusEffect& operator&=(StatusEffect& lop, StatusEffect rop) {
  return lop = lop & rop;
}

inline constexpr StatusEffect& operator^=(StatusEffect& lop, StatusEffect rop) {
  return lop = lop ^ rop;
}
} // namespace tty_invaders::effects

#endif // TTY_INVADERS_EFFECTS_STATUS_EFFECTS_H
