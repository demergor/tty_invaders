#ifndef TTY_INVADERS_ENTITIES_INVADERS_H
#define TTY_INVADERS_ENTITIES_INVADERS_H

#include <cstddef>
#include <vector>

#include "tty_invaders/effects/status_effect.h"
#include "tty_invaders/entities/projectiles.h"
#include "tty_invaders/entities/templates/projectile_body.h"
#include "tty_invaders/entities/templates/ship_body.h"
#include "tty_invaders/gameplay/collision_buffer.h"
#include "tty_invaders/rendering/term_dims.h"

namespace tty_invaders::entities {
struct Invaders {
  // TODO: Maybe add a constructor that takes a seed and generates its own invaders
  explicit Invaders(
    const std::vector<const templates::ShipBody*>& ship_bodies,
    const std::vector<const templates::ProjectileBody*>& projectile_bodies,
    const std::vector<int>& tl_xs,
    const std::vector<int>& tl_ys,
    const std::vector<int>& armor,
    const std::vector<int>& atk_spds,
    const std::vector<effects::StatusEffect> effects
  );

  void update(gameplay::CollisionBuffer&, Projectiles&, const rendering::TermDims&);
  void cleanup(Projectiles&);
  bool empty() const;

  std::vector<const templates::ShipBody*> ship_bodies;
  std::vector<const templates::ProjectileBody*> projectile_bodies;
  std::vector<int> tl_xs;
  std::vector<int> tl_ys;
  std::vector<int> armor;
  std::vector<int> refracts;
  std::vector<int> atk_spds;
  std::vector<effects::StatusEffect> effects;

private:
  void move(const rendering::TermDims&);
  void populate_collision_buffer(
    gameplay::CollisionBuffer&,
    const rendering::TermDims&
  ) const;
  void populate_projectiles(Projectiles&);
  void remove(const std::size_t idx);
  bool sizes_match() const;

  int move_refrac {0};
};
} // namespace tty_invaders::entities

#endif // TTY_INVADERS_ENTITIES_INVADERS_H
