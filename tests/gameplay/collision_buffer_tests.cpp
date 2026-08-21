#include <cstddef>
#include <format>
#include <gtest/gtest.h>
#include <string>
#include <vector>

#include "helpers/setup_helpers.h"
#include "tty_invaders/effects/collision_effect.h"
#include "tty_invaders/entities/entity_type.h"
#include "tty_invaders/entities/projectiles.h"
#include "tty_invaders/entities/templates/ships.h"
#include "tty_invaders/gameplay/collision_buffer.h"
#include "tty_invaders/gameplay/collision_data.h"
#include "tty_invaders/rendering/term_dims.h"

namespace tty_invaders::gameplay {
namespace {
std::string to_string(const std::vector<CollisionData>& collisions) {
  std::string result {"Collision vector contents: {\n"};
  for (const auto& collision : collisions) {
    result += std::format(
      "{{\neffect: {{ type: {}, val: {} }},\n"
      "target: {},\n"
      "target_id: {}\n}}",
      std::to_underlying(collision.effect.type),
      collision.effect.val,
      std::to_underlying(collision.target),
      collision.target_id
    );
  }

  return result + "\n}";
}
} // namespace

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
  ASSERT_EQ(ch.collisions.size(), expected_collision_data.size());

  for (std::size_t i {0}; i < expected_collision_data.size(); ++i) {
    const auto coll_data_equal {[expected =
                                    expected_collision_data[i]](const auto& actual) {
      return expected.effect.type == actual.effect.type
        && expected.effect.val == actual.effect.val && expected.target == actual.target
        && expected.target_id == actual.target_id;
    }};

    ASSERT_NE(
      std::find_if(ch.collisions.begin(), ch.collisions.end(), coll_data_equal),
      ch.collisions.end()
    ) << "Not found for expected collision data at index " + std::to_string(i) + "\n"
        + to_string(ch.collisions);
  }
}

TEST(CollisionBufferTests, AreaContainsTest) {
  const rendering::TermDims bounds {tests::helpers::term_dims(1, 24, 80)};
  CollisionBuffer cb {bounds};
  std::fill(cb.front_types.begin(), cb.front_types.end(), entities::EntityType::None);

  cb.front_types[2 * bounds.width + 30] = entities::EntityType::Defender;
  cb.front_types[10 * bounds.width + 60] = entities::EntityType::Defender;
  cb.front_types[13 * bounds.width + 5] = entities::EntityType::DefenderBullet;

  ASSERT_FALSE(cb.area_contains(
    25,
    0,
    entities::templates::destroyer.hitbox_pos,
    entities::EntityType::Defender,
    true,
    bounds
  ));

  ASSERT_TRUE(cb.area_contains(
    26,
    0,
    entities::templates::destroyer.hitbox_pos,
    entities::EntityType::Defender | entities::EntityType::DefenderBullet,
    true,
    bounds
  ));

  ASSERT_TRUE(cb.area_contains(
    26,
    0,
    entities::templates::destroyer.hitbox_pos,
    entities::EntityType::Defender,
    true,
    bounds
  ));

  ASSERT_FALSE(cb.area_contains(
    26,
    0,
    entities::templates::destroyer.hitbox_pos,
    entities::EntityType::DefenderBullet,
    true,
    bounds
  ));

  ASSERT_FALSE(cb.area_contains(
    5,
    10,
    entities::templates::fighter.hitbox_pos,
    entities::EntityType::DefenderBullet,
    true,
    bounds
  ));

  ASSERT_TRUE(cb.area_contains(
    5,
    11,
    entities::templates::fighter.hitbox_pos,
    entities::EntityType::Defender | entities::EntityType::DefenderBullet,
    true,
    bounds
  ));

  ASSERT_TRUE(cb.area_contains(
    5,
    11,
    entities::templates::fighter.hitbox_pos,
    entities::EntityType::DefenderBullet,
    true,
    bounds
  ));

  ASSERT_FALSE(cb.area_contains(
    5,
    11,
    entities::templates::fighter.hitbox_pos,
    entities::EntityType::Defender,
    true,
    bounds
  ));
}
} // namespace tty_invaders::gameplay
