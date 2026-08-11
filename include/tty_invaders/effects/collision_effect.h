#ifndef TTY_INVADERS_EFFECTS_COLLISION_EFFECT_H
#define TTY_INVADERS_EFFECTS_COLLISION_EFFECT_H

namespace tty_invaders::effects {
struct CollisionEffect {
  enum class Effect { Dmg, Heal, Armor, PowerUp } type;
  int val;
};
} // namespace tty_invaders::effects

#endif // TTY_INVADERS_EFFECTS_COLLISION_EFFECT_H
