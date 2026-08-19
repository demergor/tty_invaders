#ifndef TTY_INVADERS_ENTITIES_DEFENDER_H
#define TTY_INVADERS_ENTITIES_DEFENDER_H

#include <chrono>

#include "tty_invaders/effects/status_effects.h"
#include "tty_invaders/entities/projectiles.h"
#include "tty_invaders/entities/templates/ship_body.h"
#include "tty_invaders/gameplay/collision_buffer.h"
#include "tty_invaders/io/key_press.h"
#include "tty_invaders/rendering/term_dims.h"

namespace tty_invaders::entities {
struct Defender {
  explicit Defender(const templates::ShipBody* body, const int armor, const int lives);

  void move(
    const io::KeyPress&,
    const gameplay::CollisionBuffer&,
    const rendering::TermDims&
  );
  void update(gameplay::CollisionBuffer&, Projectiles&, const rendering::TermDims&);
  void cleanup(std::chrono::milliseconds);

  const templates::ShipBody* body;
  int tl_x;
  int tl_y;
  int armor;
  int lives;
  int refract;
  int atk_spd;
  effects::StatusEffect effect;
  std::chrono::milliseconds effect_duration;

private:
  void populate_coll_buf(gameplay::CollisionBuffer&, const rendering::TermDims&) const;
  void populate_projectiles(Projectiles&) const;
};
} // namespace tty_invaders::entities

#endif // TTY_INVADERS_ENTITIES_DEFENDER_H
