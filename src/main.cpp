#include <chrono>

#include "tty_invaders/entities/defender.h"
#include "tty_invaders/entities/invaders.h"
#include "tty_invaders/entities/projectiles.h"
#include "tty_invaders/entities/templates/ships.h"
#include "tty_invaders/gameplay/collision_buffer.h"
#include "tty_invaders/io/io.h"
#include "tty_invaders/io/key_press.h"
#include "tty_invaders/opts/game_settings.h"
#include "tty_invaders/random/random.h"
#include "tty_invaders/rendering/term_dims.h"

namespace tty_invaders {
int main() {
  int level {0};
  rendering::TermDims bounds {};
  gameplay::CollisionBuffer cb {bounds};
  entities::Defender defender {
    &entities::templates::fighter,
    opts::game_settings::defender_armor,
    opts::game_settings::defender_lives
  };
  entities::Invaders invaders {random::generate_invaders(level)};
  entities::Projectiles projectiles {};

  auto last_time {std::chrono::steady_clock::now()};
  while (defender.lives > 0) {
    io::KeyPress kp {io::key_pressed()};
    if (kp.type == io::KeyPress::Type::Char && kp.ch == opts::game_settings::quit_key) {
      break;
    }

    defender.move(kp, cb, bounds);
    // update loop
    // rendering (main + bar)
    // cleanup
  }

  return 0;
}
} // namespace tty_invaders
