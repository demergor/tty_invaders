#include <algorithm>
#include <cstddef>
#include <gtest/gtest.h>
#include <vector>

#include "tty_invaders/effects/collision_effect.h"
#include "tty_invaders/effects/status_effects.h"
#include "tty_invaders/entities/entity_type.h"
#include "tty_invaders/entities/invaders.h"
#include "tty_invaders/entities/projectiles.h"
#include "tty_invaders/entities/templates/projectile_body.h"
#include "tty_invaders/entities/templates/projectiles.h"
#include "tty_invaders/entities/templates/ships.h"
#include "tty_invaders/gameplay/collision_buffer.h"
#include "tty_invaders/opts/game_settings.h"
#include "tty_invaders/rendering/term_dims.h"

namespace tty_invaders::entities {
class InvaderTest : public ::testing::Test {
protected:
  inline rendering::TermDims term_dims(
    const int main_height, const int bar_height, const int width
  ) const {
    rendering::TermDims td;
    td.main_height = main_height;
    td.bar_height = bar_height;
    td.width = width;
    return td;
  }

  inline gameplay::CollisionBuffer collision_buffer(
    const rendering::TermDims& td
  ) const {
    gameplay::CollisionBuffer cb {
      .front_types {std::vector<EntityType>(
        static_cast<std::size_t>(td.main_height * td.width),
        EntityType::None
      )},
      .back_types {std::vector<EntityType>(
        static_cast<std::size_t>(td.main_height * td.width),
        EntityType::None
      )},
      .back_ids {
        std::vector<std::size_t>(static_cast<std::size_t>(td.main_height * td.width), 0)
      }
    };

    return cb;
  }

  Invaders invaders {
    {&templates::destroyer, &templates::fighter, &templates::speeder},
    {&templates::bullet, &templates::bullet, &templates::rocket},
    {10, 20, 30},
    {10, 10, 10},
    {100, 100, 100},
    {1, 1, 1},
    {0, 0, 0},
    {effects::StatusEffect::None,
     effects::StatusEffect::None,
     effects::StatusEffect::None}
  };

  Projectiles projectiles;
};

TEST_F(InvaderTest, TestProjectilesAddedToProjectiles) {
  rendering::TermDims td {term_dims(24, 1, 80)};
  gameplay::CollisionBuffer cb {collision_buffer(td)};
  invaders.update(cb, projectiles, td);

  std::vector<int> expected_xs {
    12,
    10,
    14, // destroyer
    21,
    22,
    23, // fighter
    31  // speeder
  };

  ASSERT_EQ(projectiles.xs.size(), expected_xs.size());
  for (std::size_t i {0}; i < expected_xs.size(); ++i) {
    ASSERT_EQ(projectiles.xs[i], expected_xs[i]);
  }

  std::vector<int> expected_ys {
    10,
    11,
    11, // destroyer
    10,
    10,
    10, // fighter
    10  // speeder
  };

  ASSERT_EQ(projectiles.ys.size(), expected_ys.size());
  for (std::size_t i {0}; i < expected_ys.size(); ++i) {
    ASSERT_EQ(projectiles.ys[i], expected_ys[i]);
  }

  ASSERT_TRUE(
    std::all_of(
      projectiles.x_vels.begin(),
      projectiles.x_vels.end(),
      [](const int val) { return val == 0; }
    )
  );

  ASSERT_TRUE(
    std::all_of(
      projectiles.y_vels.begin(),
      projectiles.y_vels.end(),
      [](const int val) { return val == 1; }
    )
  );

  std::vector<const templates::ProjectileBody*> expected_bodies {
    &templates::bullet,
    &templates::bullet,
    &templates::bullet,
    &templates::bullet,
    &templates::bullet,
    &templates::bullet,
    &templates::rocket
  };

  ASSERT_EQ(projectiles.bodies.size(), expected_bodies.size());
  for (std::size_t i {0}; i < expected_bodies.size(); ++i) {
    ASSERT_EQ(projectiles.bodies[i], expected_bodies[i]);
  }

  ASSERT_TRUE(
    std::all_of(
      projectiles.owners.begin(),
      projectiles.owners.end(),
      [](const EntityType val) { return val == EntityType::Invader; }
    )
  );

  ASSERT_TRUE(
    std::all_of(
      projectiles.effects.begin(),
      projectiles.effects.end(),
      [](const effects::CollisionEffect val) {
        return val.type == effects::CollisionEffect::Effect::Dmg;
      }
    )
  );

  ASSERT_TRUE(
    std::all_of(
      projectiles.effects.begin(),
      projectiles.effects.end(),
      [](const effects::CollisionEffect val) {
        return val.val == opts::game_settings::invader_atk_dmg;
      }
    )
  );
}
} // namespace tty_invaders::entities
