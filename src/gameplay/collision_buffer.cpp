#include "tty_invaders/gameplay/collision_buffer.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <stdexcept>

#include "tty_invaders/entities/entity_type.h"
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

void CollisionBuffer::clear_back() {
  std::fill(back_types.begin(), back_types.end(), entities::EntityType::None);
}
} // namespace tty_invaders::gameplay
