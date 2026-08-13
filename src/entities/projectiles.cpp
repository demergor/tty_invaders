#include "tty_invaders/entities/projectiles.h"
#include "tty_invaders/effects/collision_effect.h"

namespace tty_invaders::entities {
void Projectiles::add(
  const int x,
  const int y,
  const int x_vel,
  const int y_vel,
  const templates::ProjectileBody* body,
  const EntityType& owner,
  const effects::CollisionEffect& effect
) {
  xs.emplace_back(x);
  ys.emplace_back(y);
  x_vels.emplace_back(x_vel);
  y_vels.emplace_back(y_vel);
  bodies.emplace_back(body);
  owners.emplace_back(owner);
  effects.emplace_back(effect);
}

void Projectiles::clear() {
  xs.clear();
  ys.clear();
  x_vels.clear();
  y_vels.clear();
  bodies.clear();
  owners.clear();
  effects.clear();
}
} // namespace tty_invaders::entities
