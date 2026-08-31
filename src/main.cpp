#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>
#include <utility>
#include <vector>

#include "tty_invaders/effects/status_effect.h"
#include "tty_invaders/entities/defender.h"
#include "tty_invaders/entities/entity_type.h"
#include "tty_invaders/entities/invaders.h"
#include "tty_invaders/entities/projectiles.h"
#include "tty_invaders/entities/templates/ships.h"
#include "tty_invaders/gameplay/collision_buffer.h"
#include "tty_invaders/gameplay/collision_handler.h"
#include "tty_invaders/io/io.h"
#include "tty_invaders/io/key_press.h"
#include "tty_invaders/io/raw_term.h"
#include "tty_invaders/io/term.h"
#include "tty_invaders/opts/game_settings.h"
#include "tty_invaders/random/random.h"
#include "tty_invaders/rendering/rendering.h"
#include "tty_invaders/rendering/term_dims.h"

using namespace tty_invaders;

int main() {
  int level {1};
  io::RawTerm raw_term {};
  rendering::TermDims bounds {};
  gameplay::CollisionBuffer cb {bounds};
  gameplay::CollisionHandler ch;
  entities::Defender defender {
    &entities::templates::fighter,
    opts::game_settings::defender_armor,
    opts::game_settings::defender_lives,
    opts::game_settings::defender_atk_freq
  };

  defender.tl_x = static_cast<int>(bounds.width / 2);
  defender.tl_y = static_cast<int>(bounds.main_height - bounds.bar_height - 1)
    - (defender.body->br_y);
  defender.effect = effects::StatusEffect::None;

  entities::Invaders invaders {random::generate_invaders(level)};

  entities::Projectiles projectiles {};
  auto last_tick {std::chrono::steady_clock::now()};

  std::fill(
    cb.front_types.begin(),
    cb.front_types.end(),
    entities::EntityType::Explosion
  );

  defender.update(cb, projectiles, bounds);
  invaders.update(cb, projectiles, bounds);
  projectiles.update(cb, bounds);
  cb.dispatch_collisions(ch, projectiles);
  ch.handle_collisions(defender, invaders);
  defender.cleanup(projectiles, opts::game_settings::tick_rate);
  invaders.cleanup(projectiles);
  rendering::render_main(cb, bounds);
  rendering::render_bar(defender, bounds);
  std::swap(cb.front_types, cb.back_types);
  cb.clear_back();

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
      cb.dispatch_collisions(ch, projectiles);
      ch.handle_collisions(defender, invaders);
      defender.cleanup(projectiles, opts::game_settings::tick_rate);
      invaders.cleanup(projectiles);
      time_diff -= opts::game_settings::tick_rate;
      updated = true;
    }

    if (!updated) {
      std::this_thread::sleep_for(std::chrono::milliseconds {1});
      continue;
    }

    if (invaders.empty()) {
      invaders = random::generate_invaders(++level);
    }

    last_tick = now - time_diff;
    rendering::render_main(cb, bounds);
    rendering::render_bar(defender, bounds);
    std::swap(cb.front_types, cb.back_types);
    cb.clear_back();

    std::cout << io::term::cursor_home << io::term::yellow << "Level " << level
              << io::term::reset;

    std::cout.flush();
    std::this_thread::sleep_for(std::chrono::milliseconds {1});
  }

  return 0;
}
