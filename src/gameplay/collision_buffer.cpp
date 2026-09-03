#include "tty_invaders/gameplay/collision_buffer.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <queue>
#include <stdexcept>
#include <vector>

#include "tty_invaders/entities/entity_type.h"
#include "tty_invaders/entities/projectiles.h"
#include "tty_invaders/gameplay/collision_handler.h"
#include "tty_invaders/geometry/point.h"
#include "tty_invaders/rendering/term_dims.h"
#include "tty_invaders/utility/containers.h"

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

  assert(sizes_match());
}

void CollisionBuffer::dispatch_collisions(
  CollisionHandler& ch,
  entities::Projectiles& projectiles
) {
  for (std::size_t i {0}; i < back_types.size(); ++i) {
    if (
      entities::intersects(
        entities::EntityType::Invader | entities::EntityType::InvaderBoss,
        back_types[i]
      )
      && entities::intersects(entities::EntityType::DefenderBullet, back_types[i])
    ) {
      ch.collisions.emplace_back(
        projectiles.collision_effects[defender_bullet_ids[i]],
        entities::EntityType::Invader,
        ship_ids[i]
      );
      proj_rm.emplace_back(defender_bullet_ids[i]);
      back_types[i] |= entities::EntityType::Explosion;
      continue;
    }

    if (!entities::intersects(entities::EntityType::Defender, back_types[i])) {
      continue;
    }

    if (entities::intersects(entities::EntityType::InvaderBullet, back_types[i])) {
      ch.collisions.emplace_back(
        projectiles.collision_effects[invader_bullet_ids[i]],
        entities::EntityType::Defender,
        ship_ids[i]
      );
      proj_rm.emplace_back(invader_bullet_ids[i]);
      back_types[i] |= entities::EntityType::Explosion;
      continue;
    }

    if (entities::intersects(entities::EntityType::PowerUp, back_types[i])) {
      ch.collisions.emplace_back(
        projectiles.collision_effects[power_up_ids[i]],
        entities::EntityType::Defender,
        ship_ids[i]
      );
      proj_rm.emplace_back(power_up_ids[i]);
    }
  }

  remove_projectiles(projectiles);
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

bool CollisionBuffer::area_contains(
  const geometry::RectCoords& box,
  entities::EntityType type,
  const bool front,
  const rendering::TermDims& bounds
) const {
  const auto& types {front ? front_types : back_types};
  for (std::size_t y {box.tl_y}; y < box.br_y; y += bounds.width) {
    for (std::size_t x {box.tl_x}; x < box.br_y; ++x) {
      if (intersects(types[y + x], type)) {
        return true;
      }
    }
  }

  return false;
}

geometry::Point CollisionBuffer::find_nearest(
  geometry::Point start,
  entities::EntityType type,
  const rendering::TermDims& bounds
) const {
  struct BfsInfo {
    geometry::Point pos;
    int x_vel;
    int y_vel;
  };

  if (start.x < 0 || start.y < 0) {
    return start;
  }

  std::queue<BfsInfo> queue;
  queue.emplace(geometry::Point {start.x, start.y - 1}, 0, -1);      // up
  queue.emplace(geometry::Point {start.x + 1, start.y - 1}, 1, -1);  // right up
  queue.emplace(geometry::Point {start.x + 1, start.y}, 1, 0);       // right
  queue.emplace(geometry::Point {start.x + 1, start.y + 1}, 1, 1);   // right down
  queue.emplace(geometry::Point {start.x, start.y + 1}, 0, 1);       // down
  queue.emplace(geometry::Point {start.x - 1, start.y + 1}, -1, 1);  // left down
  queue.emplace(geometry::Point {start.x - 1, start.y}, -1, 0);      // left
  queue.emplace(geometry::Point {start.x - 1, start.y - 1}, -1, -1); // left up

  const auto width {static_cast<int>(bounds.width)};
  const auto height {static_cast<int>(bounds.main_height)};

  while (!queue.empty()) {
    auto cur {queue.front()};
    queue.pop();

    if (cur.pos.x < 0 || cur.pos.y < 0) {
      continue;
    }

    if (cur.pos.x >= width || cur.pos.y >= height) {
      continue;
    }

    const auto cb_idx {static_cast<std::size_t>(cur.pos.y * width + cur.pos.x)};
    if (intersects(back_types[cb_idx], type)) {
      return cur.pos;
    }

    if (!cur.x_vel || !cur.y_vel) {
      // TODO: remove after debugging
      // back_types[cb_idx] = entities::EntityType::Explosion;
      cur.pos.x += cur.x_vel;
      cur.pos.y += cur.y_vel;
      queue.emplace(cur);
      continue;
    }

    queue.emplace(
      geometry::Point {cur.pos.x + cur.x_vel, cur.pos.y},
      cur.x_vel,
      cur.y_vel
    );

    queue.emplace(
      geometry::Point {cur.pos.x, cur.pos.y + cur.y_vel},
      cur.x_vel,
      cur.y_vel
    );

    cur.pos.x += cur.x_vel;
    cur.pos.y += cur.y_vel;
    queue.emplace(cur);
  }

  return start;
}

void CollisionBuffer::clear_back() {
  std::fill(back_types.begin(), back_types.end(), entities::EntityType::None);
}

void CollisionBuffer::remove_projectiles(entities::Projectiles& projectiles) {
  std::ranges::sort(proj_rm, std::greater {});
  for (auto idx : proj_rm) {
    projectiles.remove(idx);
  }

  proj_rm.clear();
}

bool CollisionBuffer::sizes_match() const {
  return utility::sizes_match(
    front_types,
    back_types,
    ship_ids,
    invader_bullet_ids,
    defender_bullet_ids,
    power_up_ids
  );
}
} // namespace tty_invaders::gameplay
