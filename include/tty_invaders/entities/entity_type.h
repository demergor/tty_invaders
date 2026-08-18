#ifndef TTY_INVADERS_ENTITIES_ENTITY_TYPE_H
#define TTY_INVADERS_ENTITIES_ENTITY_TYPE_H

#include <cstdint>
#include <utility>

namespace tty_invaders::entities {
enum class EntityType : std::uint8_t {
  None = 0u,
  Defender = 1u << 0,
  DefenderBullet = 1u << 1,
  Invader = 1u << 2,
  InvaderBoss = 1u << 6,
  InvaderBullet = 1u << 3,
  PowerUp = 1u << 4,
  Explosion = 1u << 5,
};

constexpr EntityType operator|(EntityType lop, EntityType rop) {
  return static_cast<EntityType>(std::to_underlying(lop) | std::to_underlying(rop));
}

constexpr EntityType operator&(EntityType lop, EntityType rop) {
  return static_cast<EntityType>(std::to_underlying(lop) & std::to_underlying(rop));
}

constexpr EntityType operator^(EntityType lop, EntityType rop) {
  return static_cast<EntityType>(std::to_underlying(lop) ^ std::to_underlying(rop));
}

constexpr EntityType& operator|=(EntityType& lop, EntityType rop) {
  return lop = lop | rop;
}

constexpr EntityType& operator&=(EntityType& lop, EntityType rop) {
  return lop = lop & rop;
}

constexpr bool intersects(EntityType a, EntityType b) {
  return (a & b) != EntityType::None;
}

EntityType dominant_type(EntityType type);
} // namespace tty_invaders::entities

#endif // TTY_INVADERS_ENTITIES_ENTITY_TYPE_H
