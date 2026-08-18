#ifndef TTY_INVADERS_GAMEPLAY_COLLISION_HANDLER_H
#define TTY_INVADERS_GAMEPLAY_COLLISION_HANDLER_H

#include <vector>

#include "tty_invaders/gameplay/collision_data.h"

namespace tty_invaders::gameplay {
struct CollisionHandler {
  void dispatch(CollisionData);

  std::vector<CollisionData> collisions;
};
} // namespace tty_invaders::gameplay

#endif // TTY_INVADERS_GAMEPLAY_COLLISION_HANDLER_H
