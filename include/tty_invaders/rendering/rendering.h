#ifndef TTY_INVADERS_RENDERING_RENDERING_H
#define TTY_INVADERS_RENDERING_RENDERING_H

#include <vector>

#include "tty_invaders/entities/entity_type.h"

namespace tty_invaders::rendering {
RectCoords dirty_area(
  const std::vector<entities::EntityType>& old,
  const std::vector<entities::EntityType>& cur
);
} // namespace tty_invaders::rendering

#endif // TTY_INVADERS_RENDERING_RENDERING_H
