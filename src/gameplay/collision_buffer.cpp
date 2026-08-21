#include "tty_invaders/gameplay/collision_buffer.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <stdexcept>

#include "tty_invaders/entities/entity_type.h"
#include "tty_invaders/entities/projectiles.h"
#include "tty_invaders/gameplay/collision_handler.h"
#include "tty_invaders/rendering/term_dims.h"

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

// TODO: Write tests
void CollisionBuffer::dispatch_collisions(
  CollisionHandler& ch,
  const entities::Projectiles& projectiles
) const {
  for (std::size_t i {0}; i < back_types.size(); ++i) {
    if (
      entities::intersects(
        entities::EntityType::Invader | entities::EntityType::InvaderBoss,
        back_types[i]
      )
      && entities::intersects(entities::EntityType::DefenderBullet, back_types[i])
    ) {
      ch.collisions.emplace_back(
        projectiles.effects[defender_bullet_ids[i]],
        entities::EntityType::Invader,
        ship_ids[i]
      );
      continue;
    }

    if (!entities::intersects(entities::EntityType::Defender, back_types[i])) {
      continue;
    }

    if (entities::intersects(entities::EntityType::InvaderBullet, back_types[i])) {
      ch.collisions.emplace_back(
        projectiles.effects[invader_bullet_ids[i]],
        entities::EntityType::Defender,
        ship_ids[i]
      );
      continue;
    }

    if (entities::intersects(entities::EntityType::PowerUp, back_types[i])) {
      ch.collisions.emplace_back(
        projectiles.effects[power_up_ids[i]],
        entities::EntityType::Defender,
        ship_ids[i]
      );
    }
  }
}

bool CollisionBuffer::area_contains(
  const int tl_x,
  const int tl_y,
  const std::vector<geometry::Point>& offsets,
  entities::EntityType type,
  const bool front,
  const rendering::TermDims& bounds
) const {
  const auto width {static_cast<int>(bounds.width)};
  const auto height {static_cast<int>(bounds.main_height)};
  const auto& types {front ? front_types : back_types};

  for (const auto& [x_offset, y_offset] : offsets) {
    const int x_pos {tl_x + x_offset};
    if (x_pos < 0 || x_pos >= width) {
      continue;
    }

    const int y_pos {tl_y + y_offset};
    if (y_pos < 0 || y_pos >= height) {
      continue;
    }

    const int offset_idx {y_pos * width + x_pos};
    if (offset_idx < 0) {
      continue;
    }

    const auto offset_buf_idx {static_cast<std::size_t>(offset_idx)};
    if (offset_buf_idx >= types.size()) {
      continue;
    }

    if (entities::intersects(type, types[offset_buf_idx])) {
      return true;
    }
  }

  return false;
}

void CollisionBuffer::clear_back() {
  std::fill(back_types.begin(), back_types.end(), entities::EntityType::None);
}
} // namespace tty_invaders::gameplay
