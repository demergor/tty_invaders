#include "tty_invaders/entities/invaders.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <stdexcept>

#include "tty_invaders/effects/collision_effect.h"
#include "tty_invaders/effects/status_effect.h"
#include "tty_invaders/entities/entity_type.h"
#include "tty_invaders/entities/projectiles.h"
#include "tty_invaders/entities/templates/projectile_body.h"
#include "tty_invaders/entities/templates/projectiles.h"
#include "tty_invaders/entities/templates/ship_body.h"
#include "tty_invaders/gameplay/collision_buffer.h"
#include "tty_invaders/opts/game_settings.h"
#include "tty_invaders/random/random.h"
#include "tty_invaders/rendering/term_dims.h"
#include "tty_invaders/utility/containers.h"

namespace tty_invaders::entities {
Invaders::Invaders(
  const std::vector<const templates::ShipBody*>& ship_bodies,
  const std::vector<const templates::ProjectileBody*>& projectile_bodies,
  const std::vector<int>& tl_xs,
  const std::vector<int>& tl_ys,
  const std::vector<int>& armor,
  const std::vector<int>& atk_spds,
  const std::vector<effects::StatusEffect> effects
)
    : ship_bodies {ship_bodies}
    , projectile_bodies {projectile_bodies}
    , tl_xs {tl_xs}
    , tl_ys {tl_ys}
    , armor {armor}
    , refracts {std::vector(ship_bodies.size(), 0)}
    , atk_spds {atk_spds}
    , effects {effects} {
  if (tl_xs.size() != tl_ys.size()) {
    throw std::runtime_error(
      "Error initializing invaders: "
      "Amount of x-coordinates doesn't match amount of y-coordinates!"
    );
  }

  auto is_negative {[](const int val) {
    return val < 0;
  }};
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
    std::find_if(
      armor.begin(),
      armor.end(),
      [](const int val) {
        return val <= 0;
      }
    )
    != armor.end()
  ) {
    throw std::runtime_error(
      "Error initializing invaders: Lives-vector contains values < 1!"
    );
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

void Invaders::cleanup(Projectiles& projectiles) {
  std::size_t idx {0};
  while (idx < armor.size()) {
    if (armor[idx] > 0) {
      ++idx;
      continue;
    }

    if (random::random_percent() < opts::game_settings::power_up_drop_chance) {
      effects::StatusEffect effect {
        1 << random::random_uint(0, effects::string_data.size() - 2)
      };

      projectiles.add(
        tl_xs[idx],
        tl_ys[idx],
        0,
        1,
        &templates::power_up,
        EntityType::PowerUp,
        {effects::CollisionEffect::Effect::PowerUp, static_cast<int>(effect)},
        effects::StatusEffect::None
      );
    }

    remove(idx);
  }

  assert(sizes_match());
}

bool Invaders::empty() const {
  assert(sizes_match());
  return ship_bodies.empty();
}

void Invaders::move(const rendering::TermDims& bounds) {
  if (empty()) {
    return;
  }

  if (std::cmp_greater(bounds.width, *std::ranges::max_element(tl_xs) + 10)) {
    std::ranges::for_each(tl_xs, [](auto& x) {
      ++x;
    });
    return;
  }

  if (++move_refrac <= opts::game_settings::invader_move_freq) {
    return;
  }

  move_refrac = 0;
  std::ranges::for_each(tl_xs, [width = static_cast<int>(bounds.width)](auto& x) {
    x += random::random_int(-1, 1);
    x = std::clamp(x, 0, width - 1);
  });

  std::ranges::for_each(
    tl_ys,
    [height = static_cast<int>(bounds.main_height)](auto& y) {
      y += random::random_int(-1, 1);
      y = std::clamp(y, 0, height - 1);
    }
  );
}

void Invaders::populate_collision_buffer(
  gameplay::CollisionBuffer& cb,
  const rendering::TermDims& bounds
) const {
  for (std::size_t i {0}; i < tl_xs.size(); ++i) {
    for (const auto& [x_offset, y_offset] : ship_bodies[i]->hitbox_pos) {
      int hitbox_x {tl_xs[i] + x_offset};
      int hitbox_y {tl_ys[i] + y_offset};

      if (hitbox_x < 0 || hitbox_y < 0) {
        continue;
      }

      const auto grid_x {static_cast<std::size_t>(hitbox_x)};
      const auto grid_y {static_cast<std::size_t>(hitbox_y)};

      if (grid_x >= bounds.width || grid_y >= bounds.main_height) {
        continue;
      }

      std::size_t cb_idx {grid_y * bounds.width + grid_x};
      cb.back_types[cb_idx] = EntityType::Invader;
      cb.ship_ids[cb_idx] = i;
    }
  }
}

void Invaders::populate_projectiles(Projectiles& projectiles) {
  for (std::size_t i {0}; i < tl_xs.size(); ++i) {
    if (++refracts[i] <= atk_spds[i]) {
      continue;
    }

    refracts[i] = 0;
    for (const auto& idx : ship_bodies[i]->cannon_pos) {
      projectiles.add(
        tl_xs[i] + ship_bodies[i]->hitbox_pos[idx].x,
        tl_ys[i] + ship_bodies[i]->hitbox_pos[idx].y,
        0,
        1,
        projectile_bodies[i],
        EntityType::InvaderBullet,
        effects::CollisionEffect {
          .type = effects::CollisionEffect::Effect::Damage,
          .val = opts::game_settings::invader_atk_dmg
        },
        effects::StatusEffect::None
      );
    }
  }
}

void Invaders::remove(const std::size_t idx) {
  if (idx >= ship_bodies.size()) {
    throw std::runtime_error(
      "Error removing invader: Index is out of bounds!\nIndex: " + std::to_string(idx)
      + "\nSize: " + std::to_string(ship_bodies.size())
    );
  }

  ship_bodies[idx] = ship_bodies.back();
  ship_bodies.pop_back();

  projectile_bodies[idx] = projectile_bodies.back();
  projectile_bodies.pop_back();

  tl_xs[idx] = tl_xs.back();
  tl_xs.pop_back();

  tl_ys[idx] = tl_ys.back();
  tl_ys.pop_back();

  armor[idx] = armor.back();
  armor.pop_back();

  refracts[idx] = refracts.back();
  refracts.pop_back();

  atk_spds[idx] = atk_spds.back();
  atk_spds.pop_back();

  effects[idx] = effects.back();
  effects.pop_back();

  assert(sizes_match());
}

bool Invaders::sizes_match() const {
  return utility::sizes_match(
    ship_bodies,
    projectile_bodies,
    tl_xs,
    tl_ys,
    armor,
    refracts,
    atk_spds,
    effects
  );
}
} // namespace tty_invaders::entities
