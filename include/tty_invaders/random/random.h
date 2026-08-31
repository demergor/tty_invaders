#ifndef TTY_INVADERS_RANDOM_RANDOM_H
#define TTY_INVADERS_RANDOM_RANDOM_H

#include <cstddef>
#include "tty_invaders/entities/invaders.h"

namespace tty_invaders::random {
double random_percent();
std::size_t random_uint(std::size_t lower_incl, std::size_t upper_incl);
entities::Invaders generate_invaders(int level);
} // namespace tty_invaders::random

#endif // TTY_INVADERS_RANDOM_RANDOM_H
