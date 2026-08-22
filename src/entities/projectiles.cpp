#include "tty_invaders/entities/projectiles.h"

#include <cassert>
#include <cstddef>
#include <stdexcept>
#include <utility>

#include "tty_invaders/effects/collision_effect.h"
#include "tty_invaders/entities/entity_type.h"
#include "tty_invaders/gameplay/collision_buffer.h"
#include "tty_invaders/rendering/term_dims.h"
#include "tty_invaders/utility/containers.h"

namespace tty_invaders::entities {
void Projectiles::update(
  gameplay::CollisionBuffer& cb,
  const rendering::TermDims& bounds
) {
  move(bounds);
  populate_coll_buf(cb, bounds);
}

void Projectiles::add(
  const int x,
  const int y,
  const int x_vel,
  const int y_vel,
  const templates::ProjectileBody* body,
  const EntityType& type,
  const effects::CollisionEffect& effect
) {
  xs.emplace_back(x);
  ys.emplace_back(y);
  x_vels.emplace_back(x_vel);
  y_vels.emplace_back(y_vel);
  bodies.emplace_back(body);
  types.emplace_back(type);
  effects.emplace_back(effect);

  assert(utility::sizes_match(xs, ys, x_vels, y_vels, bodies, types, effects));
}

void Projectiles::clear() {
  xs.clear();
  ys.clear();
  x_vels.clear();
  y_vels.clear();
  bodies.clear();
  types.clear();
  effects.clear();

  assert(utility::sizes_match(xs, ys, x_vels, y_vels, bodies, types, effects));
}

void Projectiles::move(const rendering::TermDims& bounds) {
  const auto width {static_cast<int>(bounds.width)};
  const auto height {static_cast<int>(bounds.main_height)};
  std::size_t idx {0};

  while (idx < xs.size()) {
    xs[idx] += x_vels[idx];
    if (xs[idx] >= width || xs[idx] < 0) {
      remove(idx);
      continue;
    }

    ys[idx] += y_vels[idx];
    if (ys[idx] >= height || ys[idx] < 0) {
      remove(idx);
      continue;
    }

    ++idx;
  }

  assert(utility::sizes_match(xs, ys, x_vels, y_vels, bodies, types, effects));
}

// TODO: Write test
void Projectiles::remove(const std::size_t idx) {
  if (idx >= xs.size()) {
    throw std::runtime_error(
      "Error removing projectile: Index is out of bounds!\nIndex: "
      + std::to_string(idx) + "\nSize: " + std::to_string(xs.size())
    );
  }

  xs[idx] = xs.back();
  xs.pop_back();

  ys[idx] = ys.back();
  ys.pop_back();

  x_vels[idx] = x_vels.back();
  x_vels.pop_back();

  y_vels[idx] = y_vels.back();
  y_vels.pop_back();

  bodies[idx] = bodies.back();
  bodies.pop_back();

  types[idx] = types.back();
  types.pop_back();

  effects[idx] = effects.back();
  effects.pop_back();
}

// TODO: Write test
void Projectiles::populate_coll_buf(
  gameplay::CollisionBuffer& cb,
  const rendering::TermDims& bounds
) {
  for (std::size_t i {0}; i < xs.size(); ++i) {
    const auto grid_x {static_cast<std::size_t>(xs[i])};
    const auto grid_y {static_cast<std::size_t>(ys[i])};
    std::size_t cb_idx {grid_y * bounds.width + grid_x};
    cb.back_types[cb_idx] &= types[i];

    switch (types[i]) {
      case EntityType::DefenderBullet: cb.defender_bullet_ids[cb_idx] = i; break;
      case EntityType::InvaderBullet: cb.invader_bullet_ids[cb_idx] = i; break;
      case EntityType::PowerUp: cb.power_up_ids[cb_idx] = i; break;
      default: std::unreachable();
    }
  }
}
} // namespace tty_invaders::entities
