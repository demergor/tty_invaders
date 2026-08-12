#include "tty_invaders/entities/projectiles.h"
#include "tty_invaders/effects/collision_effect.h"

namespace tty_invaders::entities {
void Projectiles::add(
  const int tl_x,
  const int tl_y,
  const int x_vel,
  const int y_vel,
  const templates::ProjectileBody* body,
  const EntityType& owner,
  const effects::CollisionEffect& effect
) {
  tl_xs.emplace_back(tl_x);
  tl_ys.emplace_back(tl_y);
  x_vels.emplace_back(x_vel);
  y_vels.emplace_back(y_vel);
  bodies.emplace_back(body);
  owners.emplace_back(owner);
  effects.emplace_back(effect);
}

void Projectiles::clear() {
  tl_xs.clear();
  tl_ys.clear();
  x_vels.clear();
  y_vels.clear();
  bodies.clear();
  owners.clear();
  effects.clear();
}
} // namespace tty_invaders::entities
