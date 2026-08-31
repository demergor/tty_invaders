#include "tty_invaders/random/random.h"

#include <cassert>
#include <random>

#include "tty_invaders/entities/templates/projectiles.h"
#include "tty_invaders/entities/templates/ships.h"
#include "tty_invaders/gameplay/templates/formations.h"

namespace tty_invaders::random {
entities::Invaders generate_invaders(int level) {
  assert(!gameplay::templates::formations.empty());
  assert(!entities::templates::ships.empty());
  assert(!entities::templates::dmg_projectiles.empty());

  static std::uniform_int_distribution<std::size_t> formation_dist {
    0,
    gameplay::templates::formations.size() - 1
  };
  static std::uniform_int_distribution<std::size_t> ship_dist {
    0,
    entities::templates::ships.size() - 1
  };
  static std::uniform_int_distribution<std::size_t> projectile_dist {
    0,
    entities::templates::dmg_projectiles.size() - 1
  }

  // TODO: Implement
}
} // namespace tty_invaders::random
