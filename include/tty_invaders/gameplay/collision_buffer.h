#ifndef TTY_INVADERS_GAMEPLAY_COLLISION_BUFFER_H
#define TTY_INVADERS_GAMEPLAY_COLLISION_BUFFER_H

#include <cstddef>
#include <vector>

#include "tty_invaders/entities/entity_type.h"
#include "tty_invaders/gameplay/collision_handler.h"
#include "tty_invaders/geometry/point.h"
#include "tty_invaders/rendering/term_dims.h"

namespace tty_invaders::entities {
struct Defender;
struct Invaders;
struct Projectiles;
} // namespace tty_invaders::entities

namespace tty_invaders::gameplay {
struct CollisionBuffer {
  explicit CollisionBuffer(const rendering::TermDims&);

  void dispatch_collisions(CollisionHandler&, entities::Projectiles&);
  bool area_contains(
    const int tl_x,
    const int tl_y,
    const std::vector<geometry::Point>& offsets,
    entities::EntityType type,
    const bool front,
    const rendering::TermDims& bounds
  ) const;
  void clear_back();

  std::vector<entities::EntityType> front_types;
  std::vector<entities::EntityType> back_types;
  std::vector<std::size_t> ship_ids;
  std::vector<std::size_t> invader_bullet_ids;
  std::vector<std::size_t> defender_bullet_ids;
  std::vector<std::size_t> power_up_ids;
  std::vector<std::size_t> proj_rm;

private:
  bool sizes_match() const;
  void remove_projectiles(entities::Projectiles&);
};
} // namespace tty_invaders::gameplay

#endif // TTY_INVADERS_GAMEPLAY_COLLISION_BUFFER_H
