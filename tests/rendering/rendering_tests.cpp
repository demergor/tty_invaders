#include <algorithm>
#include <gtest/gtest.h>

#include "helpers/setup_helpers.h"
#include "tty_invaders/entities/entity_type.h"
#include "tty_invaders/gameplay/collision_buffer.h"
#include "tty_invaders/geometry/rect_coords.h"
#include "tty_invaders/rendering/rendering.h"
#include "tty_invaders/rendering/term_dims.h"

namespace tty_invaders::rendering {
TEST(RenderingTests, DirtyAreaFindsSmallestDirtyArea) {
  TermDims td {tests::helpers::term_dims(1, 24, 80)};
  tty_invaders::gameplay::CollisionBuffer cb {td};
  cb.back_types[4 * td.width + 8] = entities::EntityType::Invader;
  cb.back_types[20 * td.width + 1] = entities::EntityType::Invader;
  cb.back_types[5 * td.width + 77] = entities::EntityType::Invader;

  const geometry::RectCoords min_rect {dirty_area(cb, td)};
  ASSERT_EQ(min_rect.tl_x, 1);
  ASSERT_EQ(min_rect.tl_y, 4);
  ASSERT_EQ(min_rect.br_x, 78);
  ASSERT_EQ(min_rect.br_y, 21);

  TermDims td2 {tests::helpers::term_dims(1, 24, 80)};
  tty_invaders::gameplay::CollisionBuffer cb2 {td2};
  cb2.back_types[2 * td2.width + 11] = entities::EntityType::Invader;
  cb2.back_types[2 * td2.width + 12] = entities::EntityType::Invader;
  cb2.back_types[2 * td2.width + 13] = entities::EntityType::Invader;

  const geometry::RectCoords min_rect2 {dirty_area(cb2, td2)};
  ASSERT_EQ(min_rect2.tl_x, 11);
  ASSERT_EQ(min_rect2.tl_y, 2);
  ASSERT_EQ(min_rect2.br_x, 14);
  ASSERT_EQ(min_rect2.br_y, 3);
}

TEST(RenderingTests, DirtyAreaHandlesEmptyDirtyArea) {
  TermDims td {tests::helpers::term_dims(1, 24, 80)};
  tty_invaders::gameplay::CollisionBuffer cb {td};
  std::fill(
    cb.front_types.begin(),
    cb.front_types.end(),
    entities::EntityType::Defender
  );
  std::fill(cb.back_types.begin(), cb.back_types.end(), entities::EntityType::Defender);

  const geometry::RectCoords min_rect {dirty_area(cb, td)};
  ASSERT_TRUE(min_rect.empty());
}

TEST(RenderingTests, DirtyAreaRespectsTermDimsBounds) {
  TermDims td {tests::helpers::term_dims(1, 24, 80)};

  tty_invaders::gameplay::CollisionBuffer cb {td};
  std::fill(cb.back_types.begin(), cb.back_types.end(), entities::EntityType::PowerUp);

  const geometry::RectCoords min_rect {dirty_area(cb, td)};
  ASSERT_EQ(min_rect.tl_x, 0);
  ASSERT_EQ(min_rect.tl_y, 0);
  ASSERT_EQ(min_rect.br_x, 80);
  ASSERT_EQ(min_rect.br_y, 24);

  for (std::size_t i {0}; i < 10; ++i) {
    cb.front_types.emplace_back(entities::EntityType::None);
  }

  for (std::size_t i {0}; i < 10; ++i) {
    cb.back_types.emplace_back(entities::EntityType::PowerUp);
  }

  const geometry::RectCoords min_rect2 {dirty_area(cb, td)};
  ASSERT_EQ(min_rect2.tl_x, 0);
  ASSERT_EQ(min_rect2.tl_y, 0);
  ASSERT_EQ(min_rect2.br_x, 80);
  ASSERT_EQ(min_rect2.br_y, 24);
}
} // namespace tty_invaders::rendering
