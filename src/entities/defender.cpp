#include "tty_invaders/entities/defender.h"

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <stdexcept>
#include <utility>

#include "tty_invaders/effects/collision_effect.h"
#include "tty_invaders/effects/status_effect.h"
#include "tty_invaders/entities/entity_type.h"
#include "tty_invaders/entities/projectiles.h"
#include "tty_invaders/entities/templates/projectiles.h"
#include "tty_invaders/gameplay/collision_buffer.h"
#include "tty_invaders/geometry/point.h"
#include "tty_invaders/io/ctrls/arrow_direction.h"
#include "tty_invaders/io/key_press.h"
#include "tty_invaders/opts/game_settings.h"
#include "tty_invaders/rendering/term_dims.h"

namespace tty_invaders::entities {
Defender::Defender(
  const templates::ShipBody* body,
  const int armor,
  const int lives,
  const int atk_spd
)
    : body {body}
    , armor {armor}
    , lives {lives}
    , atk_spd {atk_spd} {
  if (lives <= 0) {
    throw std::runtime_error(
      "Error initializing defender: "
      "Amount of lives must be greater 0!"
    );
  }
}

void Defender::move(
  const io::KeyPress& kp,
  const gameplay::CollisionBuffer& cb,
  const rendering::TermDims& bounds
) {
  if (kp.type == io::KeyPress::Type::None) {
    return;
  }

  int x_vel {0};
  int y_vel {0};

  if (kp.type == io::KeyPress::Type::Arrow) {
    switch (kp.arrow) {
      case io::ctrls::ArrowDirection::Up: y_vel = -1; break;
      case io::ctrls::ArrowDirection::Down: y_vel = 1; break;
      case io::ctrls::ArrowDirection::Right: x_vel = 1; break;
      case io::ctrls::ArrowDirection::Left: x_vel = -1; break;
      default: std::unreachable();
    }
  } else {
    switch (kp.ch) {
      case opts::game_settings::movement::up: y_vel = -1; break;
      case opts::game_settings::movement::down: y_vel = 1; break;
      case opts::game_settings::movement::right: x_vel = 1; break;
      case opts::game_settings::movement::left: x_vel = -1; break;
      default: return;
    }
  }

  int offset_tl_x {tl_x + x_vel};
  int offset_tl_y {tl_y + y_vel};
  int offset_br_x {offset_tl_x + body->br_x};
  int offset_br_y {offset_tl_y + body->br_y};

  if (
    std::cmp_greater_equal(offset_tl_x, bounds.width) || offset_br_x < 0
    || std::cmp_greater_equal(offset_tl_y, bounds.main_height) || offset_br_y < 0
  ) {
    return;
  }

  if (
    cb.area_contains(
      offset_tl_x,
      offset_tl_y,
      body->hitbox_pos,
      EntityType::Invader | EntityType::InvaderBoss,
      true,
      bounds
    )
  ) {
    return;
  }

  tl_x += x_vel;
  tl_y += y_vel;
}

void Defender::update(
  gameplay::CollisionBuffer& cb,
  Projectiles& projectiles,
  const rendering::TermDims& bounds
) {
  populate_coll_buf(cb, bounds);
  populate_projectiles(projectiles);
}

void Defender::cleanup(Projectiles& projectiles, std::chrono::milliseconds delta_time) {
  if (armor < 0) {
    --lives;
    armor = opts::game_settings::defender_armor;
  }

  effects::StatusEffect prev_effect {effect};
  effect_duration -= std::min(effect_duration, delta_time);
  effect = (effect_duration == std::chrono::milliseconds {0})
    ? effects::StatusEffect::None
    : effect;

  if (
    prev_effect == effects::StatusEffect::Laser && effect == effects::StatusEffect::None
  ) {
    projectiles.remove(effects::StatusEffect::Laser);
  }
}

void Defender::populate_coll_buf(
  gameplay::CollisionBuffer& cb,
  const rendering::TermDims& bounds
) const {
  for (const auto& [x_offset, y_offset] : body->hitbox_pos) {
    int hitbox_x {tl_x + x_offset};
    int hitbox_y {tl_y + y_offset};

    if (hitbox_x < 0 || hitbox_y < 0) {
      continue;
    }

    const auto grid_x {static_cast<std::size_t>(hitbox_x)};
    const auto grid_y {static_cast<std::size_t>(hitbox_y)};

    if (grid_x >= bounds.width || grid_y >= bounds.main_height) {
      continue;
    }

    const std::size_t cb_idx {grid_y * bounds.width + grid_x};
    cb.back_types[cb_idx] = EntityType::Defender;
    cb.ship_ids[cb_idx] = 0;
  }
}

// TODO: Review this for complexity/readability
void Defender::populate_projectiles(Projectiles& projectiles) {
  static struct StateSnapshot {
    int tl_x;
    int tl_y;
    bool was_laser;
  } last_tick {tl_x, tl_y, false};

  bool leave_laser {
    last_tick.was_laser && tl_x == last_tick.tl_x && last_tick.tl_y == tl_y
  };

  int cur_atk_spd {atk_spd};
  switch (effect) {
    case effects::StatusEffect::DoubleAtkSpd: cur_atk_spd /= 2; break;
    case effects::StatusEffect::Laser: cur_atk_spd = -1; break;
    default: break;
  }

  if (++refract <= cur_atk_spd) {
    return;
  }

  if ((effect != effects::StatusEffect::Laser && last_tick.was_laser) || !leave_laser) {
    projectiles.remove(effects::StatusEffect::Laser);
  }

  refract = 0;
  for (const auto& idx : body->cannon_pos) {
    geometry::Point cannon_point {body->hitbox_pos[idx]};
    int cannon_x {tl_x + cannon_point.x};
    int cannon_y {tl_y + cannon_point.y};

    if (effect != effects::StatusEffect::Laser) {
      projectiles.add(
        cannon_x,
        cannon_y,
        0,
        -1,
        &templates::bullet,
        EntityType::DefenderBullet,
        effects::CollisionEffect {
          .type = effects::CollisionEffect::Effect::Damage,
          .val = opts::game_settings::defender_atk_dmg
            * (effect == effects::StatusEffect::DoubleDmg ? 2 : 1),
        },
        effect
      );

      last_tick.was_laser = false;
      continue;
    }

    if (leave_laser) {
      continue;
    }

    while (--cannon_y >= 0) {
      projectiles.add(
        cannon_x,
        cannon_y,
        0,
        0,
        &templates::bullet,
        EntityType::DefenderBullet,
        effects::CollisionEffect {
          .type = effects::CollisionEffect::Effect::Damage,
          .val = opts::game_settings::defender_atk_dmg
            * (effect == effects::StatusEffect::DoubleDmg ? 2 : 1),
        },
        effect
      );
    }
  }

  last_tick.tl_x = tl_x;
  last_tick.tl_y = tl_y;
  last_tick.was_laser = effect == effects::StatusEffect::Laser;
}
} // namespace tty_invaders::entities
