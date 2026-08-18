#include <algorithm>
#include <cstddef>
#include <gtest/gtest.h>
#include <vector>

#include "helpers/setup_helpers.h"
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

// NOTE: This test doesn't account for invader movement yet
TEST_F(InvaderTest, TestInvaderHitboxesAddedToCollisionBuffer) {
  rendering::TermDims td {tests::helpers::term_dims(1, 50, 80)};
  gameplay::CollisionBuffer cb {td};
  invaders.update(cb, projectiles, td);

  std::vector<std::size_t> expected_cb_idxs;
  for (const auto& [x_offset, y_offset] : templates::destroyer.hitbox_pos) {
    expected_cb_idxs.emplace_back(
      (10 + static_cast<std::size_t>(y_offset)) * td.width
      + (10 + static_cast<std::size_t>(x_offset))
    );
  }

  for (const auto& [x_offset, y_offset] : templates::fighter.hitbox_pos) {
    expected_cb_idxs.emplace_back(
      (10 + static_cast<std::size_t>(y_offset)) * td.width
      + (20 + static_cast<std::size_t>(x_offset))
    );
  }

  for (const auto& [x_offset, y_offset] : templates::speeder.hitbox_pos) {
    expected_cb_idxs.emplace_back(
      (10 + static_cast<std::size_t>(y_offset)) * td.width
      + (30 + static_cast<std::size_t>(x_offset))
    );
  }

  constexpr EntityType expected_entity_type {EntityType::Invader};
  std::vector<std::size_t> expected_ids {std::vector<std::size_t>(17, 0)};

  for (std::size_t i {0}; i < templates::fighter.hitbox_pos.size(); ++i) {
    expected_ids.emplace_back(1);
  }

  for (std::size_t i {0}; i < templates::speeder.hitbox_pos.size(); ++i) {
    expected_ids.emplace_back(2);
  }

  ASSERT_EQ(cb.front_types.size(), cb.back_types.size());
  ASSERT_EQ(cb.front_types.size(), cb.ship_ids.size());
  ASSERT_EQ(cb.front_types.size(), cb.invader_bullet_ids.size());

  for (std::size_t i {0}; i < expected_cb_idxs.size(); ++i) {
    ASSERT_EQ(cb.back_types[expected_cb_idxs[i]], expected_entity_type);
    ASSERT_EQ(cb.ship_ids[expected_cb_idxs[i]], expected_ids[i]);
  }
}

TEST_F(InvaderTest, TestInvaderProjectilesAddedToProjectiles) {
  rendering::TermDims td {tests::helpers::term_dims(24, 1, 80)};
  gameplay::CollisionBuffer cb {td};
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
      projectiles.types.begin(),
      projectiles.types.end(),
      [](const EntityType val) { return val == EntityType::InvaderBullet; }
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
