#include "tty_invaders/rendering/rendering.h"

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <utility>

#include "tty_invaders/entities/defender.h"
#include "tty_invaders/entities/entity_type.h"
#include "tty_invaders/gameplay/collision_buffer.h"
#include "tty_invaders/geometry/rect_coords.h"
#include "tty_invaders/io/term.h"
#include "tty_invaders/opts/game_settings.h"
#include "tty_invaders/rendering/formatting.h"
#include "tty_invaders/rendering/render_attr.h"
#include "tty_invaders/rendering/term_dims.h"

namespace tty_invaders::rendering {
// TODO: Write tests and maybe make the rendering functions return strings to cout
// myself
void render_bar(const entities::Defender& defender, const TermDims& bounds) {
  if (bounds.width < 2) {
    return;
  }

  auto available_width {static_cast<int>(bounds.width)};
  std::string result;
  result.reserve(
    opts::game_settings::action_bar_height * bounds.width
    * expected_render_bytes_per_cell
  );

  io::term::move_cursor(result, 0, bounds.main_height);
  result += io::term::clear_line;

  if (std::cmp_less(bounds.width, defender.lives)) {
    result += std::to_string(defender.lives);
    result += io::term::red;
    result += io::term::bold;
    result += opts::game_settings::heart;
    available_width -= 4;
  } else {
    result += io::term::red;
    result += io::term::bold;
    result +=
      std::string(static_cast<std::size_t>(defender.lives), opts::game_settings::heart);
    available_width -= defender.lives + 2;
  }

  result += io::term::reset;
  effects::StatusEffectStrData data {str_data(defender.effect)};
  if (static_cast<std::size_t>(available_width) >= data.num_chars) {
    result += io::term::cursor_right;
    io::term::move_cursor(result, bounds.width - data.num_chars, bounds.main_height);
    result += data.str;
    result += io::term::reset;
  }

  io::term::move_cursor(result, 0, bounds.main_height + 1);
  std::size_t armor_bar {
    (bounds.width * static_cast<std::size_t>(defender.armor))
    / opts::game_settings::defender_armor
  };

  double armor_percent {(defender.armor * 100.0) / opts::game_settings::defender_armor};
  if (armor_percent < opts::game_settings::low_percentage) {
    result += io::term::red;
  } else if (armor_percent < opts::game_settings::mid_percentage) {
    result += io::term::yellow;
  } else {
    result += io::term::green;
  }

  result += std::string(armor_bar, 'X');
  result += io::term::reset;
  std::cout << result;
  std::cout.flush();
}

// TODO: Test
void render_main(const gameplay::CollisionBuffer& cb, const TermDims& bounds) {
  geometry::RectCoords min_rect {dirty_area(cb, bounds)};
  if (min_rect.empty()) {
    return;
  }

  std::string result;
  result.reserve(
    (min_rect.br_x - min_rect.tl_x) * min_rect.br_y * expected_render_bytes_per_cell
  );

  Formatting prev {Formatting::None};
  for (std::size_t y {min_rect.tl_y}; y < min_rect.br_y; ++y) {
    io::term::move_cursor(result, min_rect.tl_x, y);
    for (std::size_t x {min_rect.tl_x}; x < min_rect.br_x; ++x) {
      RenderAttr ra {dominant_type(cb.back_types[y * bounds.width + x])};
      result += ansi_escape(prev, ra.formatting);
      result += ra.ch;
    }
  }

  std::cout << result << io::term::reset;
}

geometry::RectCoords dirty_area(
  const gameplay::CollisionBuffer& cb,
  const TermDims& bounds
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
