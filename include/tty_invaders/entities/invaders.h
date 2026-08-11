#ifndef TTY_INVADERS_ENTITIES_INVADERS_H
#define TTY_INVADERS_ENTITIES_INVADERS_H

#include <vector>

#include "tty_invaders/effects/status_effects.h"
#include "tty_invaders/entities/templates/ship_body.h"
#include "tty_invaders/gameplay/collision_buffer.h"

namespace tty_invaders::entities {
struct Invaders {
  // TODO: Maybe add a constructor that takes a seed and generate its own invaders
  explicit Invaders(
    const std::vector<const templates::ShipBody*> bodies,
    const std::vector<int>& tl_xs,
    const std::vector<int>& tl_ys,
    const std::vector<int>& armor,
    const std::vector<int>& lives,
    const std::vector<int>& atk_spds,
    const std::vector<effects::StatusEffect> effects
  );

  void update(gameplay::CollisionBuffer&);

  std::vector<const templates::ShipBody*> bodies;
  std::vector<int> tl_xs;
  std::vector<int> tl_ys;
  std::vector<int> br_xs;
  std::vector<int> br_ys;

  std::vector<int> armor;
  std::vector<int> lives;

  std::vector<int> refracts;
  std::vector<int> atk_spds;
  std::vector<effects::StatusEffect> effects;
};
} // namespace tty_invaders::entities

#endif // TTY_INVADERS_ENTITIES_INVADERS_H
