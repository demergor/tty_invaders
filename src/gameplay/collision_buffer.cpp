#include "tty_invaders/gameplay/collision_buffer.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <stdexcept>

#include "tty_invaders/entities/entity_type.h"
#include "tty_invaders/geometry/rect_coords.h"
#include "tty_invaders/rendering/term_dims.h"

namespace tty_invaders::gameplay {
CollisionBuffer::CollisionBuffer(const rendering::TermDims& td)
    : front_types {std::vector<entities::EntityType>(
        td.main_height * td.width, entities::EntityType::None
      )}
    , back_types {std::vector<entities::EntityType>(
        td.main_height * td.width, entities::EntityType::None
      )}
    , back_ids {std::vector<std::size_t>(td.main_height * td.width, 0)} {
  assert(
    front_types.size() == back_types.size() && front_types.size() == back_ids.size()
  );

  if (front_types.empty()) {
    throw std::runtime_error(
      "Error initializing collision buffer: "
      "Terminal dimension area is empty!"
    );
  }
}

bool CollisionBuffer::area_contains(
  const geometry::RectCoords& area,
  entities::EntityType type,
  const rendering::TermDims& bounds
) const {
  for (std::size_t y_offset {area.tl_y * bounds.width}; y_offset < area.br_y;
       y_offset += bounds.width) {
    for (std::size_t x {area.tl_x}; x < area.br_x; ++x) {
      if (entities::is_subset(type, front_types[y_offset + x])) {
        return true;
      }
    }
  }

  return false;
}

bool CollisionBuffer::area_contains_only(
  const std::size_t idx,
  const std::vector<geometry::Point>& offsets,
  entities::EntityType type,
  const rendering::TermDims& bounds
) {
  const auto width {static_cast<int>(bounds.width)};
  const auto buf_offset {static_cast<int>(idx)};

  for (const auto& [x_offset, y_offset] : offsets) {
    const int offset_idx {buf_offset + x_offset + y_offset * width};
    if (offset_idx < 0) {
      continue;
    }

    const auto offset_buf_idx {static_cast<std::size_t>(offset_idx)};
    if (offset_buf_idx >= back_types.size()) {
      continue;
    }

    if (!is_subset(back_types[offset_buf_idx], type)) {
      return false;
    }
  }

  return true;
}

void CollisionBuffer::clear_back() {
  std::fill(back_types.begin(), back_types.end(), entities::EntityType::None);
}
} // namespace tty_invaders::gameplay
