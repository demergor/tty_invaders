#ifndef TTY_INVADERS_RANDOM_RANDOM_H
#define TTY_INVADERS_RANDOM_RANDOM_H

#include "tty_invaders/entities/invaders.h"
namespace tty_invaders::random {
int random_int(int level);
entities::Invaders generate_invaders(int level);
} // namespace tty_invaders::random

#endif // TTY_INVADERS_RANDOM_RANDOM_H
