#include "tty_invaders/entities/projectiles.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <limits>
#include <stdexcept>
#include <utility>

#include "tty_invaders/effects/collision_effect.h"
#include "tty_invaders/effects/status_effect.h"
#include "tty_invaders/entities/entity_type.h"
#include "tty_invaders/entities/invaders.h"
#include "tty_invaders/gameplay/collision_buffer.h"
#include "tty_invaders/geometry/point.h"
#include "tty_invaders/rendering/term_dims.h"
#include "tty_invaders/utility/containers.h"

namespace tty_invaders::entities {
void Projectiles::update(
  gameplay::CollisionBuffer& cb,
  const Invaders& invaders,
  const rendering::TermDims& bounds
) {
  move(invaders, bounds);
  populate_coll_buf(cb, bounds);
}

void Projectiles::add(
  const int x,
  const int y,
  const int x_vel,
  const int y_vel,
  const templates::ProjectileBody* body,
  const EntityType& type,
  const effects::CollisionEffect& collision_effect,
  const effects::StatusEffect& status_effect
) {
  xs.emplace_back(x);
  ys.emplace_back(y);
  x_vels.emplace_back(x_vel);
  y_vels.emplace_back(y_vel);
  bodies.emplace_back(body);
  types.emplace_back(type);
  collision_effects.emplace_back(collision_effect);
  status_effects.emplace_back(status_effect);

  assert(vec_sizes_match());
}

void Projectiles::clear() {
  xs.clear();
  ys.clear();
  x_vels.clear();
  y_vels.clear();
  bodies.clear();
  types.clear();
  collision_effects.clear();
  status_effects.clear();

  assert(vec_sizes_match());
}

void Projectiles::move(const Invaders& invaders, const rendering::TermDims& bounds) {
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

    if (status_effects[idx] != effects::StatusEffect::Homing) {
      ++idx;
      continue;
    }

    assert(xs[idx] >= 0);
    assert(ys[idx] >= 0);

    auto min_dist {std::numeric_limits<int>::max()};
    for (std::size_t i {0}; i < invaders.tl_xs.size(); ++i) {
      const std::size_t middle_idx {invaders.ship_bodies[i]->hitbox_pos.size() / 2};
      geometry::Point middle_hitpoint {invaders.ship_bodies[i]->hitbox_pos[middle_idx]};
      int hitbox_x {invaders.tl_xs[i] + middle_hitpoint.x};
      int hitbox_y {invaders.tl_ys[i] + middle_hitpoint.y};

      if (
        hitbox_x < 0 || static_cast<std::size_t>(hitbox_x) >= bounds.width
        || hitbox_y < 0 || static_cast<std::size_t>(hitbox_y) >= bounds.main_height
      ) {
        continue;
      }

      int xs_diff {hitbox_x - xs[idx]};
      int ys_diff {hitbox_y - ys[idx]};
      int cur_dist {std::abs(xs_diff) + std::abs(ys_diff)};

      if (cur_dist >= min_dist) {
        continue;
      }

      x_vels[idx] = std::clamp(xs_diff, -1, 1);
      y_vels[idx] = std::clamp(ys_diff, -1, 1);
      min_dist = cur_dist;
    }

    ++idx;
  }

  assert(vec_sizes_match());
}

void Projectiles::remove(effects::StatusEffect effect) {
  std::size_t idx {0};
  while (idx < status_effects.size()) {
    if (status_effects[idx] == effect) {
      remove(idx);
    } else {
      ++idx;
    }
  }

  assert(vec_sizes_match());
}

void Projectiles::remove(std::size_t idx) {
  assert (!xs.empty());
  assert (idx < xs.size());

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

  collision_effects[idx] = collision_effects.back();
  collision_effects.pop_back();

  status_effects[idx] = status_effects.back();
  status_effects.pop_back();
}

// TODO: Write test
void Projectiles::populate_coll_buf(
  gameplay::CollisionBuffer& cb,
  const rendering::TermDims& bounds
) {
  for (std::size_t i {0}; i < xs.size(); ++i) {
    for (auto [x_offset, y_offset] : bodies[i]->points) {
      const int hitbox_x {xs[i] + x_offset};
      const int hitbox_y {ys[i] + y_offset};

      if (hitbox_x < 0 || hitbox_y < 0) {
        continue;
      }

      const auto grid_x {static_cast<std::size_t>(hitbox_x)};
      const auto grid_y {static_cast<std::size_t>(hitbox_y)};

      if (grid_x >= bounds.width || grid_y >= bounds.main_height) {
        continue;
      }

      std::size_t cb_idx {grid_y * bounds.width + grid_x};
      cb.back_types[cb_idx] |= types[i];

      switch (types[i]) {
        case EntityType::DefenderBullet: cb.defender_bullet_ids[cb_idx] = i; break;
        case EntityType::InvaderBullet: cb.invader_bullet_ids[cb_idx] = i; break;
        case EntityType::PowerUp: cb.power_up_ids[cb_idx] = i; break;
        default: std::unreachable();
      }
    }
  }
}

bool Projectiles::vec_sizes_match() const {
  return utility::sizes_match(
    xs,
    ys,
    x_vels,
    y_vels,
    bodies,
    types,
    collision_effects,
    status_effects
  );
}
} // namespace tty_invaders::entities
