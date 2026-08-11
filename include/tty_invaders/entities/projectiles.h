#ifndef TTY_INVADERS_ENTITIES_PROJECTILES_H
#define TTY_INVADERS_ENTITIES_PROJECTILES_H

#include <vector>

#include "tty_invaders/effects/collision_effect.h"
#include "tty_invaders/entities/entity_type.h"
#include "tty_invaders/gameplay/collision_buffer.h"
#include "tty_invaders/rendering/render_attr.h"

namespace tty_invaders::entities {
struct Projectiles {
  void update(gameplay::CollisionBuffer&);
  void clear();

  std::vector<int> tl_xs;
  std::vector<int> tl_ys;
  std::vector<int> x_vels;
  std::vector<int> y_vels;
  std::vector<const ProjectileBody*> bodies;
  std::vector<EntityType> owners;
  std::vector<effects::CollisionEffect> effects;
  std::vector<rendering::RenderAttr> render_attrs;
};
} // namespace tty_invaders::entities

#endif // TTY_INVADERS_ENTITIES_PROJECTILES_H
