#include "tty_invaders/gameplay/collision_buffer.h"

#include <algorithm>

#include "tty_invaders/entities/entity_type.h"

namespace tty_invaders::gameplay {
void CollisionBuffer::clear_back() {
  std::fill(back_types.begin(), back_types.end(), entities::EntityType::None);
}
} // namespace tty_invaders::gameplay
