#include "tty_invaders/random/random.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <random>
#include <vector>

#include "tty_invaders/effects/status_effect.h"
#include "tty_invaders/entities/invaders.h"
#include "tty_invaders/entities/templates/projectiles.h"
#include "tty_invaders/entities/templates/ships.h"
#include "tty_invaders/gameplay/templates/formations.h"
#include "tty_invaders/opts/game_settings.h"

namespace tty_invaders::random {
double random_percent() {
  static std::uniform_real_distribution<double> dist {0.0, 100.0};
  static std::mt19937 rng {opts::game_settings::invader_level_seed};

  return dist(rng);
}

int random_int (int lower_incl, int upper_incl) {
  static std::mt19937 rng {opts::game_settings::invader_level_seed};
  std::uniform_int_distribution<int> dist {lower_incl, upper_incl};

  return dist(rng);
}

std::size_t random_uint(std::size_t lower_incl, std::size_t upper_incl) {
  static std::mt19937 rng {opts::game_settings::invader_level_seed};
  std::uniform_int_distribution<std::size_t> dist {lower_incl, upper_incl};

  return dist(rng);
}

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
  };

  const std::random_device::result_type seed {
    opts::game_settings::invader_level_seed
    + static_cast<std::random_device::result_type>(level)
  };
  std::mt19937 rng {seed};

  const std::vector<geometry::Point>& formation {
    *gameplay::templates::formations[formation_dist(rng)]
  };

  std::size_t cost_limit {formation.size() + static_cast<std::size_t>(level)};
  auto max_ship_idx {static_cast<std::size_t>(std::distance(
    entities::templates::ship_costs.begin(),
    std::ranges::max_element(
      entities::templates::ship_costs,
      [cost_limit, amount = formation.size()](auto a, auto b) {
        return a <= b && a * amount > cost_limit;
      }
    )
  ))};
  cost_limit -= entities::templates::ship_costs.at(max_ship_idx) * formation.size();

  auto max_proj_idx {static_cast<std::size_t>(std::distance(
    entities::templates::dmg_projectile_costs.begin(),
    std::ranges::max_element(
      entities::templates::dmg_projectile_costs,
      [cost_limit, amount = formation.size()](auto a, auto b) {
        return a <= b && a * amount > cost_limit;
      }
    )
  ))};

  static std::vector<int> tl_xs;
  tl_xs.reserve(formation.size());
  std::ranges::transform(formation, std::back_inserter(tl_xs), [](const auto& point) {
    return point.x;
  });

  static std::vector<int> tl_ys;
  tl_ys.reserve(formation.size());
  std::ranges::transform(formation, std::back_inserter(tl_ys), [](const auto& point) {
    return point.y;
  });

  entities::Invaders invaders {
    std::vector(formation.size(), entities::templates::ships[max_ship_idx]),
    std::vector(formation.size(), entities::templates::dmg_projectiles[max_proj_idx]),
    tl_xs,
    tl_ys,
    std::vector(formation.size(), opts::game_settings::invader_armor),
    std::vector(formation.size(), opts::game_settings::invader_atk_freq),
    std::vector(formation.size(), effects::StatusEffect::None)
  };

  tl_xs.clear();
  tl_ys.clear();

  return invaders;
}
} // namespace tty_invaders::random
