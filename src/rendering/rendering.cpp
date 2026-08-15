#include "tty_invaders/rendering/rendering.h"

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>

#include "tty_invaders/entities/entity_type.h"
#include "tty_invaders/gameplay/collision_buffer.h"
#include "tty_invaders/geometry/rect_coords.h"
#include "tty_invaders/rendering/formatting.h"
#include "tty_invaders/rendering/render_attr.h"
#include "tty_invaders/rendering/term_dims.h"

namespace tty_invaders::rendering {
void render(
  const gameplay::CollisionBuffer& cb,
  const geometry::RectCoords bounds,
  const TermDims& td
) {
  std::string result;
  result.reserve(
    static_cast<std::size_t>((bounds.br_x - bounds.tl_x) * bounds.br_y)
    * expected_render_bytes_per_cell
  );

  const std::size_t x_start {static_cast<std::size_t>(std::max(bounds.tl_x, 0))};
  const std::size_t x_end {static_cast<std::size_t>(std::max(bounds.br_x, 0))};
  const std::size_t y_start {static_cast<std::size_t>(std::max(bounds.tl_y, 0))};
  const std::size_t y_end {static_cast<std::size_t>(std::max(bounds.br_y, 0))};

  Formatting prev {Formatting::None};
  for (std::size_t i {y_start}; i < y_end; ++i) {
    for (std::size_t j {x_start}; j < x_end; ++j) {
      RenderAttr ra;
      switch (cb.back_types[i * td.width + j]) {
        case entities::EntityType::Bullet:
          ra.formatting = Formatting::Yellow;
          ra.ch = 'o';
          break;
        case entities::EntityType::Defender:
          ra.formatting = Formatting::Bold | Formatting::BrightGreen;
          ra.ch = 'D';
          break;
        case entities::EntityType::Invader:
          ra.formatting = Formatting::Red;
          ra.ch = 'V';
          break;
        case entities::EntityType::PowerUp:
          ra.formatting = Formatting::Bold | Formatting::BrightBlue;
          ra.ch = 'P';
          break;
        default:
          ra.formatting = Formatting::None;
          ra.ch = ' ';
          break;
      }

      result += ansi_escape(prev, ra.formatting);
      result += ra.ch;
    }

    std::cout << result;
  }
}

std::string ansi_escape(const Formatting& prev, const Formatting& cur) {
  // TODO: Implement
}

geometry::RectCoords dirty_area(
  const std::vector<entities::EntityType>& old,
  const std::vector<entities::EntityType>& cur
) {
  // TODO: Implement
}
} // namespace tty_invaders::rendering
