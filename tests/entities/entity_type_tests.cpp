#include <gtest/gtest.h>

#include "tty_invaders/entities/entity_type.h"
#include "tty_invaders/opts/game_settings.h"

namespace tty_invaders::entities {
TEST(EntityTypeTests, DominantTypeTest) {
  ASSERT_NE(
    opts::game_settings::entity_type_priority[2],
    dominant_type(
      EntityType::None | EntityType::Defender | EntityType::DefenderBullet
      | EntityType::Invader | EntityType::InvaderBoss | EntityType::InvaderBullet
      | EntityType::PowerUp | EntityType::Explosion
    )
  );

  ASSERT_EQ(
    opts::game_settings::entity_type_priority[0],
    dominant_type(
      EntityType::None | EntityType::Defender | EntityType::DefenderBullet
      | EntityType::Invader | EntityType::InvaderBoss | EntityType::InvaderBullet
      | EntityType::PowerUp | EntityType::Explosion
    )
  );

  ASSERT_EQ(
    opts::game_settings::entity_type_priority[1],
    dominant_type(
      EntityType::None | EntityType::Defender | EntityType::DefenderBullet
      | EntityType::Invader | EntityType::InvaderBoss | EntityType::InvaderBullet
      | EntityType::Explosion
    )
  );

  ASSERT_EQ(
    opts::game_settings::entity_type_priority[2],
    dominant_type(
      EntityType::None | EntityType::Defender | EntityType::DefenderBullet
      | EntityType::Invader | EntityType::InvaderBoss | EntityType::InvaderBullet
    )
  );

  ASSERT_EQ(
    opts::game_settings::entity_type_priority[3],
    dominant_type(
      EntityType::None | EntityType::Defender | EntityType::DefenderBullet
      | EntityType::Invader | EntityType::InvaderBullet
    )
  );

  ASSERT_EQ(
    opts::game_settings::entity_type_priority[4],
    dominant_type(
      EntityType::None | EntityType::DefenderBullet | EntityType::Invader
      | EntityType::InvaderBullet
    )
  );

  ASSERT_EQ(
    opts::game_settings::entity_type_priority[5],
    dominant_type(
      EntityType::None | EntityType::DefenderBullet | EntityType::InvaderBullet
    )
  );

  ASSERT_EQ(
    opts::game_settings::entity_type_priority[6],
    dominant_type(EntityType::None | EntityType::DefenderBullet)
  );

  ASSERT_EQ(
    opts::game_settings::entity_type_priority[7],
    dominant_type(EntityType::None)
  );
}
} // namespace tty_invaders::entities
