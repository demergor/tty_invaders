#include <gtest/gtest.h>

#include "helpers/setup_helpers.h"
#include "tty_invaders/entities/entity_type.h"
#include "tty_invaders/gameplay/collision_buffer.h"
#include "tty_invaders/geometry/rect_coords.h"
#include "tty_invaders/rendering/term_dims.h"

namespace tty_invaders::gameplay {
TEST(CollisionBufferTests, AreaContainsTests) {
  const rendering::TermDims bounds {tests::helpers::term_dims(1, 24, 80)};
  CollisionBuffer cb {bounds};

  cb.front_types[30] = entities::EntityType::Defender;
  cb.front_types[10 * bounds.width + 60] = entities::EntityType::Defender;
  cb.front_types[13 * bounds.width + 5] = entities::EntityType::DefenderBullet;

  geometry::RectCoords area_nothing {.tl_x = 6, .tl_y = 1, .br_x = 59, .br_y = 12};
  ASSERT_FALSE(cb.area_contains(
    area_nothing,
    entities::EntityType::Defender | entities::EntityType::DefenderBullet,
    bounds
  ));

  geometry::RectCoords area_defender {.tl_x = 30, .tl_y = 0, .br_x = 61, .br_y = 11};
  ASSERT_TRUE(cb.area_contains(area_defender, entities::EntityType::Defender, bounds));
  ASSERT_TRUE(cb.area_contains(
    area_defender,
    entities::EntityType::Defender | entities::EntityType::DefenderBullet,
    bounds
  ));

  geometry::RectCoords area_both {.tl_x = 5, .tl_y = 0, .br_x = 61, .br_y = 14};
  ASSERT_TRUE(cb.area_contains(
    area_both,
    entities::EntityType::Defender | entities::EntityType::DefenderBullet,
    bounds
  ));

  geometry::RectCoords area_empty {.tl_x = 60, .tl_y = 10, .br_x = 60, .br_y = 11};
  ASSERT_FALSE(cb.area_contains(
    area_empty,
    entities::EntityType::Defender | entities::EntityType::DefenderBullet,
    bounds
  ));
}
} // namespace tty_invaders::gameplay
