#include "tty_invaders/entities/entity_type.h"

#include <utility>

#include "tty_invaders/opts/game_settings.h"
#include "tty_invaders/utility/mask.h"

namespace tty_invaders::entities {
// TODO: Test
EntityType dominant_type(EntityType type) {
  for (const auto entity_type : opts::game_settings::entity_type_priority) {
    if (utility::mask::is_subset(entity_type, type)) {
      return entity_type;
    }
  }

  std::unreachable();
}
} // namespace tty_invaders::entities
