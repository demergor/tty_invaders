#include <algorithm>
#include <cassert>
#include <cstddef>
#include <stdexcept>

#include "tty_invaders/entities/entity_type.h"
#include "tty_invaders/entities/projectiles.h"
#include "tty_invaders/gameplay/collision_buffer.h"
#include "tty_invaders/gameplay/collision_handler.h"
#include "tty_invaders/geometry/rect_coords.h"
#include "tty_invaders/rendering/term_dims.h"
#include "tty_invaders/utility/mask.h"

namespace tty_invaders::gameplay {
CollisionBuffer::CollisionBuffer(const rendering::TermDims& td)
  : front_types {std::vector<entities::EntityType>(
      td.main_height * td.width,
      entities::EntityType::None
    )}
  , back_types {std::vector<entities::EntityType>(
      td.main_height * td.width,
      entities::EntityType::None
    )}
  , ship_ids {std::vector<std::size_t>(td.main_height * td.width, 0)}
  , invader_bullet_ids {std::vector<std::size_t>(td.main_height * td.width, 0)}
  , defender_bullet_ids {std::vector<std::size_t>(td.main_height * td.width, 0)}
  , power_up_ids {std::vector<std::size_t>(td.main_height * td.width, 0)} {
  assert(
    front_types.size() == back_types.size() && front_types.size() == ship_ids.size()
  );

  if (front_types.empty()) {
    throw std::runtime_error(
      "Error initializing collision buffer: "
      "Terminal dimension area is empty!"
    );
  }
}

void CollisionBuffer::dispatch_collisions(
  CollisionHandler& ch,
  const entities::Projectiles& projectiles
) const {
  for (std::size_t i {0}; i < back_types.size(); ++i) {
    constexpr auto ship_types {
      entities::EntityType::Defender | entities::EntityType::Invader
      | entities::EntityType::InvaderBoss
    };
    constexpr auto projectile_types {
      entities::EntityType::DefenderBullet | entities::EntityType::InvaderBullet
      | entities::EntityType::PowerUp
    };

    if (
      !entities::intersects(back_types[i], ship_types)
      || !entities::intersects(back_types[i], projectile_types)
    ) {
      continue;
    }

    if (
      entities::intersects(
        back_types[i],
        entities::EntityType::Invader | entities::EntityType::InvaderBoss
          | entities::EntityType::DefenderBullet
      )
    ) {
      ch.collisions.emplace_back(
        projectiles.effects[defender_bullet_ids[i]],
        entities::EntityType::Invader,
        ship_ids[i]
      );
      continue;
    }

    if (entities::intersects(back_types[i], entities::EntityType::InvaderBullet)) {
      ch.collisions.emplace_back(
        projectiles.effects[invader_bullet_ids[i]],
        entities::EntityType::Defender,
        ship_ids[i]
      );
      continue;
    }

    if (entities::intersects(back_types[i], entities::EntityType::PowerUp)) {
      ch.collisions.emplace_back(
        projectiles.effects[invader_bullet_ids[i]],
        entities::EntityType::Defender,
        ship_ids[i]
      );
    }
  }
}

bool CollisionBuffer::area_contains(
  const geometry::RectCoords& area,
  entities::EntityType type,
  const bool front,
  const rendering::TermDims& bounds
) const {
  const auto& types {front ? front_types : back_types};
  for (
    std::size_t y_offset {area.tl_y * bounds.width};
    y_offset < area.br_y * bounds.width;
    y_offset += bounds.width
  ) {
    for (std::size_t x {area.tl_x}; x < area.br_x; ++x) {
      if (utility::mask::is_subset(type, types[y_offset + x])) {
        return true;
      }
    }
  }

  return false;
}

// TODO: Write test or change overload test to match this signature
bool CollisionBuffer::area_contains(
  const std::size_t idx,
  const std::vector<geometry::Point>& offsets,
  entities::EntityType type,
  const bool front,
  const rendering::TermDims& bounds
) const {
  const auto width {static_cast<int>(bounds.width)};
  const auto buf_offset {static_cast<int>(idx)};
  const auto& types {front ? front_types : back_types};

  for (const auto& [x_offset, y_offset] : offsets) {
    const int offset_idx {buf_offset + x_offset + y_offset * width};
    if (offset_idx < 0) {
      continue;
    }

    const auto offset_buf_idx {static_cast<std::size_t>(offset_idx)};
    if (offset_buf_idx >= types.size()) {
      continue;
    }

    if (utility::mask::is_subset(type, types[offset_buf_idx])) {
      return true;
    }
  }

  return false;
}

void CollisionBuffer::clear_back() {
  std::fill(back_types.begin(), back_types.end(), entities::EntityType::None);
}
} // namespace tty_invaders::gameplay
