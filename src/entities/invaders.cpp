#include "tty_invaders/entities/invaders.h"

#include <algorithm>
#include <cstddef>
#include <stdexcept>

#include "tty_invaders/effects/collision_effect.h"
#include "tty_invaders/entities/entity_type.h"
#include "tty_invaders/entities/projectiles.h"
#include "tty_invaders/entities/templates/projectile_body.h"
#include "tty_invaders/entities/templates/ship_body.h"
#include "tty_invaders/gameplay/collision_buffer.h"
#include "tty_invaders/opts/game_settings.h"
#include "tty_invaders/rendering/term_dims.h"

namespace tty_invaders::entities {
Invaders::Invaders(
  const std::vector<const templates::ShipBody*>& ship_bodies,
  const std::vector<const templates::ProjectileBody*>& projectile_bodies,
  const std::vector<int>& tl_xs,
  const std::vector<int>& tl_ys,
  const std::vector<int>& armor,
  const std::vector<int>& lives,
  const std::vector<int>& atk_spds,
  const std::vector<effects::StatusEffect> effects
)
    : ship_bodies {ship_bodies}
    , projectile_bodies {projectile_bodies}
    , tl_xs {tl_xs}
    , tl_ys {tl_ys}
    , armor {armor}
    , lives {lives}
    , atk_spds {atk_spds}
    , effects {effects} {
  if (tl_xs.size() != tl_ys.size()) {
    throw std::runtime_error(
      "Error initializing invaders: "
      "Amount of x-coordinates doesn't match amount of y-coordinates!"
    );
  }

  auto is_negative {[](const int val) { return val < 0; }};
  if (std::find_if(armor.begin(), armor.end(), is_negative) != armor.end()) {
    throw std::runtime_error(
      "Error initializing invaders: Armor-vector contains negative values!"
    );
  }

  if (std::find_if(atk_spds.begin(), atk_spds.end(), is_negative) != atk_spds.end()) {
    throw std::runtime_error(
      "Error initializing invaders: Attack-speeds-vector contains negative values!"
    );
  }

  if (
    std::find_if(lives.begin(), lives.end(), [](const int val) { return val <= 0; })

    != lives.end()
  ) {
    throw std::runtime_error(
      "Error initializing invaders: Lives-vector contains values < 1!"
    );
  }

  br_xs.reserve(tl_xs.size());
  for (std::size_t i {0}; i < tl_xs.size(); ++i) {
    br_xs.emplace_back(tl_xs[i] + ship_bodies[i]->br_x);
  }

  br_ys.reserve(tl_ys.size());
  for (std::size_t i {0}; i < tl_ys.size(); ++i) {
    br_ys.emplace_back(tl_ys[i] + ship_bodies[i]->br_y);
  }
}

void Invaders::update(
  gameplay::CollisionBuffer& cb,
  Projectiles& projectiles,
  const rendering::TermDims& bounds
) {
  move(bounds);
  populate_collision_buffer(cb, bounds);
  populate_projectiles(projectiles);
}

// TODO: Implement
void Invaders::move(const rendering::TermDims& bounds) {
  return;
}

void Invaders::populate_collision_buffer(
  gameplay::CollisionBuffer& cb, const rendering::TermDims& bounds
) const {
  for (std::size_t i {0}; i < tl_xs.size(); ++i) {
    for (const auto& [x_offset, y_offset] : ship_bodies[i]->hitbox_pos) {
      int hitbox_x {tl_xs[i] + x_offset};
      int hitbox_y {tl_ys[i] + y_offset};

      if (hitbox_x < 0 || hitbox_y < 0) {
        continue;
      }

      std::size_t grid_x {static_cast<std::size_t>(hitbox_x)};
      std::size_t grid_y {static_cast<std::size_t>(hitbox_y)};

      if (grid_x >= bounds.width || grid_y >= bounds.main_height) {
        continue;
      }

      std::size_t cb_idx {grid_y * bounds.width + grid_x};
      cb.back_types[cb_idx] = EntityType::Invader;
      cb.back_ids[cb_idx] = i;
    }
  }
}

void Invaders::populate_projectiles(Projectiles& projectiles) const {
  for (std::size_t i {0}; i < tl_xs.size(); ++i) {
    for (const auto& idx : ship_bodies[i]->cannon_pos) {
      projectiles.add(
        tl_xs[i] + ship_bodies[i]->hitbox_pos[idx].x,
        tl_ys[i] + ship_bodies[i]->hitbox_pos[idx].y,
        0,
        1,
        projectile_bodies[i],
        EntityType::Invader,
        effects::CollisionEffect {
          .type = effects::CollisionEffect::Effect::Dmg,
          .val = opts::game_settings::invader_atk_dmg
        }
      );
    }
  }
}
} // namespace tty_invaders::entities
