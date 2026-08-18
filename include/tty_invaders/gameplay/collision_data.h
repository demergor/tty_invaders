#ifndef TTY_INVADERS_GAMEPLAY_COLLISION_DATA_H
#define TTY_INVADERS_GAMEPLAY_COLLISION_DATA_H

#include <cstddef>

#include "tty_invaders/effects/collision_effect.h"
#include "tty_invaders/entities/entity_type.h"

namespace tty_invaders::gameplay {
struct CollisionData {
  effects::CollisionEffect effect;
  entities::EntityType target;
  std::size_t target_id;
};
} // namespace tty_invaders::gameplay

#endif // TTY_INVADERS_GAMEPLAY_COLLISION_DATA_H
