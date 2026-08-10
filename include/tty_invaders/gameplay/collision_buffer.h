#ifndef TTY_INVADERS_GAMEPLAY_COLLISION_BUFFER_H
#define TTY_INVADERS_GAMEPLAY_COLLISION_BUFFER_H

#include <cstddef>
#include <vector>

#include "tty_invaders/entities/entity_type.h"

namespace tty_invaders::gameplay {
struct CollisionBuffer {
  std::vector<entities::EntityType> front_types;
  std::vector<entities::EntityType> back_types;
  std::vector<std::size_t> back_ids;

  void clear_back();
};
} // namespace tty_invaders::gameplay

#endif // TTY_INVADERS_GAMEPLAY_COLLISION_BUFFER_H
