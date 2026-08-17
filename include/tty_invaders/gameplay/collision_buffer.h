#ifndef TTY_INVADERS_GAMEPLAY_COLLISION_BUFFER_H
#define TTY_INVADERS_GAMEPLAY_COLLISION_BUFFER_H

#include <cstddef>
#include <vector>

#include "tty_invaders/entities/entity_type.h"
#include "tty_invaders/geometry/rect_coords.h"
#include "tty_invaders/rendering/term_dims.h"

namespace tty_invaders::gameplay {
struct CollisionBuffer {
  explicit CollisionBuffer(const rendering::TermDims&);

  bool area_contains(
    const geometry::RectCoords&, entities::EntityType, const rendering::TermDims&
  ) const;
  void clear_back();

  std::vector<entities::EntityType> front_types;
  std::vector<entities::EntityType> back_types;
  std::vector<std::size_t> back_ids;
};
} // namespace tty_invaders::gameplay

#endif // TTY_INVADERS_GAMEPLAY_COLLISION_BUFFER_H
