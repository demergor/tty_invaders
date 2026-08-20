#include <chrono>
#include <thread>
#include <utility>
#include <vector>

#include "tty_invaders/effects/status_effects.h"
#include "tty_invaders/entities/defender.h"
#include "tty_invaders/entities/invaders.h"
#include "tty_invaders/entities/projectiles.h"
#include "tty_invaders/entities/templates/projectiles.h"
#include "tty_invaders/entities/templates/ships.h"
#include "tty_invaders/gameplay/collision_buffer.h"
#include "tty_invaders/io/io.h"
#include "tty_invaders/io/key_press.h"
#include "tty_invaders/io/raw_term.h"
#include "tty_invaders/opts/game_settings.h"
#include "tty_invaders/rendering/rendering.h"
#include "tty_invaders/rendering/term_dims.h"

using namespace tty_invaders;

int main() {
  int level {0};
  io::RawTerm raw_term {};
  rendering::TermDims bounds {};
  gameplay::CollisionBuffer cb {bounds};
  entities::Defender defender {
    &entities::templates::fighter,
    opts::game_settings::defender_armor,
    opts::game_settings::defender_lives,
    opts::game_settings::defender_atk_freq
  };

  defender.tl_x = static_cast<int>(bounds.width / 2);
  defender.tl_y = static_cast<int>(bounds.main_height) - defender.body->br_y + 1;

  entities::Invaders invaders {
    std::vector(8, &entities::templates::fighter),
    std::vector(8, &entities::templates::rocket),
    std::vector {10, 20, 30, 40, 50, 20, 30, 40},
    std::vector {0, 0, 0, 0, 0, 10, 10, 10},
    std::vector(8, 1),
    std::vector(8, 10),
    std::vector(8, effects::StatusEffect::None)
  };
  // entities::Invaders invaders {random::generate_invaders(level)};
  entities::Projectiles projectiles {};
  auto last_tick {std::chrono::steady_clock::now()};

  while (defender.lives > 0) {
    io::KeyPress kp {io::key_pressed()};
    if (kp.type == io::KeyPress::Type::Char && kp.ch == opts::game_settings::quit_key) {
      break;
    }
    
    defender.move(kp, cb, bounds);
    const auto now {std::chrono::steady_clock::now()};
    auto time_diff {now - last_tick};
    bool updated {false};

    while (time_diff >= opts::game_settings::tick_rate) {
      defender.update(cb, projectiles, bounds);
      invaders.update(cb, projectiles, bounds);
      projectiles.update(cb, bounds);
      std::swap(cb.front_types, cb.back_types);
      defender.cleanup(opts::game_settings::tick_rate);
      time_diff -= opts::game_settings::tick_rate;
      updated = true;
    }

    if (updated) {
      last_tick = now - time_diff;
      rendering::render_main(cb, bounds);
      rendering::render_bar(defender, bounds);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds {1});
  }

  return 0;
}
