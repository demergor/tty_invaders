#ifndef TTY_INVADERS_EFFECTS_COLLISION_EFFECT_H
#define TTY_INVADERS_EFFECTS_COLLISION_EFFECT_H

#include <utility>

namespace tty_invaders::effects {
struct CollisionEffect {
  enum class Effect { Damage, Heal, Armor, PowerUp } type;
  int val;
};

inline constexpr bool operator==(
  CollisionEffect::Effect lop, CollisionEffect::Effect rop
) {
  return std::to_underlying(lop) == std::to_underlying(rop);
}

inline constexpr bool operator!=(
  CollisionEffect::Effect lop, CollisionEffect::Effect rop
) {
  return !(lop == rop);
}

inline constexpr CollisionEffect::Effect operator|(
  CollisionEffect::Effect lop, CollisionEffect::Effect rop
) {
  return static_cast<CollisionEffect::Effect>(
    std::to_underlying(lop) | std::to_underlying(rop)
  );
}

inline constexpr CollisionEffect::Effect operator&(
  CollisionEffect::Effect lop, CollisionEffect::Effect rop
) {
  return static_cast<CollisionEffect::Effect>(
    std::to_underlying(lop) & std::to_underlying(rop)
  );
}

inline constexpr CollisionEffect::Effect operator^(
  CollisionEffect::Effect lop, CollisionEffect::Effect rop
) {
  return static_cast<CollisionEffect::Effect>(
    std::to_underlying(lop) ^ std::to_underlying(rop)
  );
}

inline constexpr CollisionEffect::Effect& operator|=(
  CollisionEffect::Effect& lop, CollisionEffect::Effect rop
) {
  return lop = lop | rop;
}

inline constexpr CollisionEffect::Effect& operator&=(
  CollisionEffect::Effect& lop, CollisionEffect::Effect rop
) {
  return lop = lop & rop;
}

inline constexpr CollisionEffect::Effect& operator^=(
  CollisionEffect::Effect& lop, CollisionEffect::Effect rop
) {
  return lop = lop ^ rop;
}
} // namespace tty_invaders::effects

#endif // TTY_INVADERS_EFFECTS_COLLISION_EFFECT_H
