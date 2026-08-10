#ifndef TTY_INVADERS_EFFECTS_STATUS_EFFECTS_H
#define TTY_INVADERS_EFFECTS_STATUS_EFFECTS_H

#include <cstdint>

namespace tty_invaders::effects {
enum class StatusEffect : uint8_t {
  None = 0u,
  DoubleAtkSpd = 1u << 0,
  DoubleDmg = 1u << 1,
  Invincible = 1u << 2,
  Homing = 1u << 3,
  Laser = 1u << 4
};
} // namespace tty_invaders::effects

// TODO: Add bitwise logic

#endif // TTY_INVADERS_EFFECTS_STATUS_EFFECTS_H
