#ifndef TTY_INVADERS_ENTITIES_DEFENDER_H
#define TTY_INVADERS_ENTITIES_DEFENDER_H

#include "tty_invaders/effects/status_effects.h"
#include "tty_invaders/entities/templates/ship_body.h"

namespace tty_invaders::entities {
struct Defender {
  templates::ShipBody body;
  int tl_x, tl_y, br_x, br_y;
  int armor;
  int lives;
  int refract;
  int atk_spd;
  effects::StatusEffect effect;

  explicit Defender(const templates::ShipBody* body, const int armor, const int lives);

  void move();
  void update();
};
} // namespace tty_invaders::entities

#endif // TTY_INVADERS_ENTITIES_DEFENDER_H
