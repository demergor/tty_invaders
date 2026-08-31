#ifndef TTY_INVADERS_GAMEPLAY_TEMPLATES_FORMATIONS_H
#define TTY_INVADERS_GAMEPLAY_TEMPLATES_FORMATIONS_H

#include <vector>

#include "tty_invaders/geometry/point.h"

namespace tty_invaders::gameplay::templates {
extern const std::vector<geometry::Point> triangle;
extern const std::vector<geometry::Point> block;

const std::vector<std::vector<geometry::Point>> formations {triangle, block};
} // namespace tty_invaders::gameplay::templates

#endif // TTY_INVADERS_GAMEPLAY_TEMPLATES_FORMATIONS_H
