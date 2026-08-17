#ifndef TTY_INVADERS_ENTITIES_DEFENDER_H
#define TTY_INVADERS_ENTITIES_DEFENDER_H

#include "tty_invaders/effects/status_effects.h"
#include "tty_invaders/entities/templates/ship_body.h"
#include "tty_invaders/io/key_press.h"
#include "tty_invaders/rendering/term_dims.h"

namespace tty_invaders::entities {
struct Defender {
  explicit Defender(templates::ShipBody* body, const int armor, const int lives);

  void move(const io::KeyPress&, const rendering::TermDims&);
  void update();

  templates::ShipBody* body;
  int tl_x;
  int tl_y;
  int armor;
  int lives;
  int refract;
  int atk_spd;
  effects::StatusEffect effect;
};
} // namespace tty_invaders::entities

#endif // TTY_INVADERS_ENTITIES_DEFENDER_H
