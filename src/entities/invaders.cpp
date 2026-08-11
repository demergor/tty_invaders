#include "tty_invaders/entities/invaders.h"

#include <algorithm>
#include <cstddef>
#include <stdexcept>

#include "tty_invaders/entities/templates/ship_body.h"
#include "tty_invaders/gameplay/collision_buffer.h"

namespace tty_invaders::entities {
Invaders::Invaders(
  const std::vector<const templates::ShipBody*> bodies,
  const std::vector<int>& tl_xs,
  const std::vector<int>& tl_ys,
  const std::vector<int>& armor,
  const std::vector<int>& lives,
  const std::vector<int>& atk_spds,
  const std::vector<effects::StatusEffect> effects
)
    : bodies {bodies}
    , tl_xs {tl_xs}
    , tl_ys {tl_ys}
    , armor {armor}
    , lives {lives}
    , atk_spds {atk_spds}
    , effects {effects} {
  if (tl_xs.size() != tl_ys.size()) {
    throw std::runtime_error(
      "Error initializing invaders: "
      "Amount of x-coordinates doesn't match amount of y-coordinates!"
    );
  }

  auto is_negative {[](const int val) { return val < 0; }};
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
    std::find_if(lives.begin(), lives.end(), [](const int val) { return val <= 0; })
    != lives.end()
  ) {
    throw std::runtime_error(
      "Error initializing invaders: Lives-vector contains values < 1!"
    );
  }

  br_xs.reserve(tl_xs.size());
  for (std::size_t i {0}; i < tl_xs.size(); ++i) {
    br_xs.emplace_back(tl_xs[i] + bodies[i]->br_x);
  }

  br_ys.reserve(tl_ys.size());
  for (std::size_t i {0}; i < tl_ys.size(); ++i) {
    br_ys.emplace_back(tl_ys[i] + bodies[i]->br_y);
  }
}

void Invaders::update(gameplay::CollisionBuffer& cb) {
  // TODO: Add Invader move semantics (writing to cb)
  // TODO: Add bullet creation (decide update-order of entities)
}
} // namespace tty_invaders::entities
