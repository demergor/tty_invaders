#include <cstddef>
#include <gtest/gtest.h>

#include "helpers/setup_helpers.h"
#include "tty_invaders/effects/collision_effect.h"
#include "tty_invaders/entities/entity_type.h"
#include "tty_invaders/entities/projectiles.h"
#include "tty_invaders/entities/templates/ships.h"
#include "tty_invaders/gameplay/collision_buffer.h"
#include "tty_invaders/gameplay/collision_data.h"
#include "tty_invaders/rendering/term_dims.h"

namespace tty_invaders::gameplay {
TEST(CollisionBufferTests, DispatchCollisionsTest) {
  rendering::TermDims bounds {tests::helpers::term_dims(1, 24, 80)};
  CollisionBuffer cb {bounds};
  CollisionHandler ch {};

  std::size_t cb_idx {10 * bounds.width + 30};
  cb.back_types[cb_idx] =
    entities::EntityType::Defender | entities::EntityType::DefenderBullet;
  cb.ship_ids[cb_idx] = 0;
  cb.defender_bullet_ids[cb_idx] = 0;

  cb_idx = 10 * bounds.width + 40;
  cb.back_types[cb_idx] =
    entities::EntityType::Defender | entities::EntityType::InvaderBullet;
  cb.ship_ids[cb_idx] = 0;
  cb.invader_bullet_ids[cb_idx] = 1;

  cb_idx = 20 * bounds.width + 30;
  cb.back_types[cb_idx] =
    entities::EntityType::Invader | entities::EntityType::DefenderBullet;
  cb.ship_ids[cb_idx] = 0;
  cb.defender_bullet_ids[cb_idx] = 2;

  cb_idx = 20 * bounds.width + 40;
  cb.back_types[cb_idx] =
    entities::EntityType::InvaderBoss | entities::EntityType::DefenderBullet;
  cb.ship_ids[cb_idx] = 1;
  cb.defender_bullet_ids[cb_idx] = 3;

  cb_idx = 20 * bounds.width + 50;
  cb.back_types[cb_idx] =
    entities::EntityType::Invader | entities::EntityType::InvaderBullet;
  cb.ship_ids[cb_idx] = 2;
  cb.invader_bullet_ids[cb_idx] = 4;

  cb_idx = 21 * bounds.width + 40;
  cb.back_types[cb_idx] = entities::EntityType::Invader | entities::EntityType::PowerUp;
  cb.ship_ids[cb_idx] = 3;
  cb.power_up_ids[cb_idx] = 5;

  cb_idx = 21 * bounds.width + 50;
  cb.back_types[cb_idx] =
    entities::EntityType::Defender | entities::EntityType::PowerUp;
  cb.ship_ids[cb_idx] = 0;
  cb.power_up_ids[cb_idx] = 6;

  // Should be ignored by CollisionHandler
  cb.back_types[22 * bounds.width + 10] = entities::EntityType::Defender;
  cb.back_types[22 * bounds.width + 20] = entities::EntityType::Invader;
  cb.back_types[22 * bounds.width + 30] = entities::EntityType::InvaderBoss;
  cb.back_types[22 * bounds.width + 40] = entities::EntityType::Explosion;

  std::vector<CollisionData> expected_collision_data {
    {{effects::CollisionEffect::Effect::Damage, 50}, entities::EntityType::Defender, 0},
    {{effects::CollisionEffect::Effect::Damage, 50}, entities::EntityType::Invader, 0},
    {{effects::CollisionEffect::Effect::Damage, 50}, entities::EntityType::Invader, 0},
    {{effects::CollisionEffect::Effect::PowerUp, 1}, entities::EntityType::Defender, 0},
  };

  entities::Projectiles projectiles {
    {}, // tl_xs
    {}, // tl_ys
    {}, // x_vels
    {}, // y_vels
    {}, // bodies
    {entities::EntityType::DefenderBullet,
      entities::EntityType::InvaderBullet,
      entities::EntityType::DefenderBullet,
      entities::EntityType::DefenderBullet,
      entities::EntityType::InvaderBullet,
      entities::EntityType::PowerUp,
      entities::EntityType::PowerUp}, // types
    {{effects::CollisionEffect::Effect::Damage, 50},
      {effects::CollisionEffect::Effect::Damage, 50},
      {effects::CollisionEffect::Effect::Damage, 50},
      {effects::CollisionEffect::Effect::Damage, 50},
      {effects::CollisionEffect::Effect::Damage, 50},
      {effects::CollisionEffect::Effect::PowerUp, 1},
      {effects::CollisionEffect::Effect::PowerUp, 1}} // effects
  };

  cb.dispatch_collisions(ch, projectiles);
  const auto coll_data_equal {[](const CollisionData& a, const CollisionData& b) {
    return a.effect.type == b.effect.type && a.effect.val == b.effect.val
      && a.target == b.target && a.target_id == b.target_id;
  }};

  for (std::size_t i {0}; i < expected_collision_data.size(); ++i) {
    ASSERT_TRUE(coll_data_equal(expected_collision_data[i], ch.collisions[i]));
  }
}

TEST(CollisionBufferTests, AreaContainsTest) {
  const rendering::TermDims bounds {tests::helpers::term_dims(1, 24, 80)};
  CollisionBuffer cb {bounds};

  cb.front_types[2 * bounds.width + 30] = entities::EntityType::Defender;
  cb.front_types[10 * bounds.width + 60] = entities::EntityType::Defender;
  cb.front_types[13 * bounds.width + 5] = entities::EntityType::DefenderBullet;

  std::size_t y_offset {2 * bounds.width};
  ASSERT_FALSE(cb.area_contains(
    y_offset + 25,
    entities::templates::destroyer.hitbox_pos,
    entities::EntityType::Defender | entities::EntityType::DefenderBullet,
    true,
    bounds
  ));

  ASSERT_TRUE(cb.area_contains(
    y_offset + 26,
    entities::templates::destroyer.hitbox_pos,
    entities::EntityType::Defender | entities::EntityType::DefenderBullet,
    true,
    bounds
  ));

  ASSERT_TRUE(cb.area_contains(
    y_offset + 26,
    entities::templates::destroyer.hitbox_pos,
    entities::EntityType::Defender,
    true,
    bounds
  ));

  ASSERT_FALSE(cb.area_contains(
    y_offset + 26,
    entities::templates::destroyer.hitbox_pos,
    entities::EntityType::DefenderBullet,
    true,
    bounds
  ));

  y_offset = 10 * bounds.width;
  ASSERT_FALSE(cb.area_contains(
    y_offset + 5,
    entities::templates::fighter.hitbox_pos,
    entities::EntityType::Defender | entities::EntityType::DefenderBullet,
    true,
    bounds
  ));

  y_offset = 11 * bounds.width;
  ASSERT_TRUE(cb.area_contains(
    y_offset + 5,
    entities::templates::fighter.hitbox_pos,
    entities::EntityType::Defender | entities::EntityType::DefenderBullet,
    true,
    bounds
  ));

  ASSERT_FALSE(cb.area_contains(
    y_offset + 5,
    entities::templates::fighter.hitbox_pos,
    entities::EntityType::Defender,
    true,
    bounds
  ));

  ASSERT_FALSE(cb.area_contains(
    y_offset + 5,
    entities::templates::fighter.hitbox_pos,
    entities::EntityType::DefenderBullet,
    true,
    bounds
  ));
}
} // namespace tty_invaders::gameplay
