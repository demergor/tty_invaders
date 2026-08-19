#include "tty_invaders/entities/defender.h"
#include "tty_invaders/entities/invaders.h"
#include "tty_invaders/entities/templates/ships.h"
#include "tty_invaders/opts/game_settings.h"

namespace tty_invaders {
int main() {
  entities::Defender defender {
    &entities::templates::fighter,
    opts::game_settings::defender_armor,
    opts::game_settings::defender_lives
  };

  entities::Invaders invaders {};

  return 0;
}
} // namespace tty_invaders
