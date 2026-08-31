#ifndef TTY_INVADERS_ENTITIES_TEMPLATES_SHIPS_H
#define TTY_INVADERS_ENTITIES_TEMPLATES_SHIPS_H

#include <cstddef>

#include "tty_invaders/entities/templates/ship_body.h"

namespace tty_invaders::entities::templates {
extern const ShipBody destroyer;
extern const ShipBody fighter;
extern const ShipBody speeder;

extern const std::vector<const ShipBody*> ships;
extern const std::vector<std::size_t> ship_costs;
} // namespace tty_invaders::entities::templates

#endif // TTY_INVADERS_ENTITIES_TEMPLATES_SHIPS_H
