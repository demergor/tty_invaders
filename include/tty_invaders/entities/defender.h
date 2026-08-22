#ifndef TTY_INVADERS_ENTITIES_DEFENDER_H
#define TTY_INVADERS_ENTITIES_DEFENDER_H

#include <chrono>

#include "tty_invaders/effects/status_effect.h"
#include "tty_invaders/entities/projectiles.h"
#include "tty_invaders/entities/templates/ship_body.h"
#include "tty_invaders/gameplay/collision_buffer.h"
#include "tty_invaders/io/key_press.h"
#include "tty_invaders/opts/game_settings.h"
#include "tty_invaders/rendering/term_dims.h"

namespace tty_invaders::entities {
struct Defender {
  explicit Defender(
    const templates::ShipBody* body,
    const int armor,
    const int lives,
    const int atk_spd
  );

  void move(
    const io::KeyPress&,
    const gameplay::CollisionBuffer&,
    const rendering::TermDims&
  );
  void update(gameplay::CollisionBuffer&, Projectiles&, const rendering::TermDims&);
  void cleanup(Projectiles&, const std::chrono::milliseconds);

  const templates::ShipBody* body;
  int tl_x {0};
  int tl_y {0};
  int armor;
  int lives;
  int refract {0};
  int atk_spd;
  effects::StatusEffect effect {effects::StatusEffect::None};
  std::chrono::milliseconds effect_duration {
    opts::game_settings::status_effect_duration
  };

private:
  void populate_coll_buf(gameplay::CollisionBuffer&, const rendering::TermDims&) const;
  void populate_projectiles(Projectiles&);
};
} // namespace tty_invaders::entities

#endif // TTY_INVADERS_ENTITIES_DEFENDER_H
