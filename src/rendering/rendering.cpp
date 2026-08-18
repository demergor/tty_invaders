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
void render(const gameplay::CollisionBuffer& cb, const TermDims& td) {
  geometry::RectCoords min_rect {dirty_area(cb, td)};
  if (min_rect.empty()) {
    return;
  }

  std::string result;
  result.reserve(
    (min_rect.br_x - min_rect.tl_x) * min_rect.br_y * expected_render_bytes_per_cell
  );

  Formatting prev {Formatting::None};
  for (std::size_t y {min_rect.tl_y}; y < min_rect.br_y; ++y) {
    for (std::size_t x {min_rect.tl_x}; x < min_rect.br_x; ++x) {
      RenderAttr ra {dominant_type(cb.back_types[y * td.width + x])};
      result += ansi_escape(prev, ra.formatting);
      result += ra.ch;
    }

    std::cout << result;
  }
}

geometry::RectCoords dirty_area(
  const gameplay::CollisionBuffer& cb, const TermDims& bounds
) {
  geometry::RectCoords dirty_area {};
  bool first {true};

  for (std::size_t y {0}; y < bounds.main_height; ++y) {
    for (std::size_t x {0}; x < bounds.width; ++x) {
      std::size_t cb_idx {y * bounds.width + x};
      if (cb.back_types[cb_idx] == cb.front_types[cb_idx]) {
        continue;
      }

      if (first) {
        dirty_area.tl_x = x;
        dirty_area.tl_y = y;
        dirty_area.br_x = x + 1;
        dirty_area.br_y = y + 1;
        first = false;
        continue;
      }

      dirty_area.tl_x = std::min(x, dirty_area.tl_x);
      dirty_area.tl_y = std::min(y, dirty_area.tl_y);
      dirty_area.br_x = std::max(x + 1, dirty_area.br_x);
      dirty_area.br_y = std::max(y + 1, dirty_area.br_y);
    }
  }

  return dirty_area;
}
} // namespace tty_invaders::rendering
