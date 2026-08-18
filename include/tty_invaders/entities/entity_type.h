#ifndef TTY_INVADERS_ENTITIES_ENTITY_TYPE_H
#define TTY_INVADERS_ENTITIES_ENTITY_TYPE_H

#include <cstdint>
#include <utility>

namespace tty_invaders::entities {
enum class EntityType : std::uint8_t {
  None,
  Defender,
  DefenderBullet,
  Invader,
  InvaderBullet,
  PowerUp
};

inline constexpr EntityType operator|(const EntityType& lop, const EntityType& rop) {
  return static_cast<EntityType>(std::to_underlying(lop) | std::to_underlying(rop));
}

inline constexpr EntityType operator&(const EntityType& lop, const EntityType& rop) {
  return static_cast<EntityType>(std::to_underlying(lop) & std::to_underlying(rop));
}

inline constexpr bool is_subset(EntityType subset, EntityType superset) {
  return (superset & subset) == subset;
}
} // namespace tty_invaders::entities

#endif // TTY_INVADERS_ENTITIES_ENTITY_TYPE_H
