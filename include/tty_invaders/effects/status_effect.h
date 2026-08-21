#ifndef TTY_INVADERS_EFFECTS_STATUS_EFFECT_H
#define TTY_INVADERS_EFFECTS_STATUS_EFFECT_H

#include <array>
#include <cstddef>
#include <string>
#include <utility>

#include "tty_invaders/io/term.h"

namespace tty_invaders::effects {
enum class StatusEffect : int {
  None = 0u,
  DoubleAtkSpd = 1u << 0,
  DoubleDmg = 1u << 1,
  Invincible = 1u << 2,
  Homing = 1u << 3,
  Laser = 1u << 4
};

struct StatusEffectStrData {
  std::string str;
  std::size_t num_chars;
};

const std::array string_data {
  std::pair {
    StatusEffect::None,
    StatusEffectStrData {std::string {io::term::dim} + "No effect", 9}
  },
  std::pair {
    StatusEffect::DoubleAtkSpd,
    StatusEffectStrData {std::string {io::term::yellow} + "2x ATK SPD", 10}
  },
  std::pair {
    StatusEffect::DoubleDmg,
    StatusEffectStrData {std::string {io::term::red} + "2x ATK DMG", 10}
  },
  std::pair {
    StatusEffect::Invincible,
    StatusEffectStrData {std::string {io::term::blue} + "Invincible", 10}
  },
  std::pair {
    StatusEffect::Homing,
    StatusEffectStrData {std::string {io::term::grey} + "Homing", 6}
  },
  std::pair {
    StatusEffect::Laser,
    StatusEffectStrData {std::string {io::term::green} + "Laser", 5}
  },
};

inline const StatusEffectStrData& str_data(StatusEffect effect) {
  for (const auto& [status_effect, str_data] : string_data) {
    if (effect == status_effect) {
      return str_data;
    }
  }

  std::unreachable();
}

constexpr bool operator==(StatusEffect lop, StatusEffect rop) {
  return std::to_underlying(lop) == std::to_underlying(rop);
}

constexpr bool operator!=(StatusEffect lop, StatusEffect rop) {
  return !(lop == rop);
}

constexpr StatusEffect operator|(StatusEffect lop, StatusEffect rop) {
  return static_cast<StatusEffect>(std::to_underlying(lop) | std::to_underlying(rop));
}

constexpr StatusEffect operator&(StatusEffect lop, StatusEffect rop) {
  return static_cast<StatusEffect>(std::to_underlying(lop) & std::to_underlying(rop));
}

constexpr StatusEffect operator^(StatusEffect lop, StatusEffect rop) {
  return static_cast<StatusEffect>(std::to_underlying(lop) ^ std::to_underlying(rop));
}

constexpr StatusEffect& operator|=(StatusEffect& lop, StatusEffect rop) {
  return lop = lop | rop;
}

constexpr StatusEffect& operator&=(StatusEffect& lop, StatusEffect rop) {
  return lop = lop & rop;
}

constexpr StatusEffect& operator^=(StatusEffect& lop, StatusEffect rop) {
  return lop = lop ^ rop;
}
} // namespace tty_invaders::effects

#endif // TTY_INVADERS_EFFECTS_STATUS_EFFECT_H
