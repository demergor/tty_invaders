#ifndef TTY_INVADERS_ENTITIES_PROJECTILES_H
#define TTY_INVADERS_ENTITIES_PROJECTILES_H

#include <cstddef>
#include <vector>

#include "tty_invaders/effects/collision_effect.h"
#include "tty_invaders/effects/status_effect.h"
#include "tty_invaders/entities/entity_type.h"
#include "tty_invaders/entities/templates/projectile_body.h"
#include "tty_invaders/gameplay/collision_buffer.h"
#include "tty_invaders/rendering/term_dims.h"

namespace tty_invaders::entities {
struct Projectiles {
  void update(gameplay::CollisionBuffer&, const rendering::TermDims&);
  void add(
    const int tl_x,
    const int tl_y,
    const int x_vel,
    const int y_vel,
    const templates::ProjectileBody* body,
    const EntityType& owner,
    const effects::CollisionEffect& collision_effect,
    const effects::StatusEffect& status_effect
  );
  void remove(std::size_t idx);
  void remove(effects::StatusEffect);
  void clear();

  std::vector<int> xs;
  std::vector<int> ys;
  std::vector<int> x_vels;
  std::vector<int> y_vels;
  std::vector<const templates::ProjectileBody*> bodies;
  std::vector<EntityType> types;
  std::vector<effects::CollisionEffect> collision_effects;
  std::vector<effects::StatusEffect> status_effects;

private:
  void move(const gameplay::CollisionBuffer&, const rendering::TermDims&);
  void populate_coll_buf(gameplay::CollisionBuffer&, const rendering::TermDims&);
  bool vec_sizes_match() const;
};
} // namespace tty_invaders::entities

#endif // TTY_INVADERS_ENTITIES_PROJECTILES_H
