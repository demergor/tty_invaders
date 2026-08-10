#include <gtest/gtest.h>

#include "tty_invaders/entities/entity_type.h"
#include "tty_invaders/gameplay/collision_buffer.h"

TEST(CollisionBufferTests, ClearSetsAllToNone) {
  tty_invaders::gameplay::CollisionBuffer cb;
  cb.clear_back();

  for (const auto& type : cb.back_types) {
    ASSERT_EQ(type, tty_invaders::entities::EntityType::None);
  }
}
