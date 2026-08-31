#ifndef TTY_INVADERS_ENTITIES_TEMPLATES_PROJECTILES_H
#define TTY_INVADERS_ENTITIES_TEMPLATES_PROJECTILES_H

#include <cstddef>
#include <vector>
#include "tty_invaders/entities/templates/projectile_body.h"

namespace tty_invaders::entities::templates {
extern const ProjectileBody bullet;
extern const ProjectileBody power_up;
extern const ProjectileBody rocket;

const std::vector<const ProjectileBody*> dmg_projectiles {&bullet, &rocket};
const std::vector<std::size_t> dmg_projectile_costs {0, 5};
} // namespace tty_invaders::entities::templates

#endif // TTY_INVADERS_ENTITIES_TEMPLATES_PROJECTILES_H
