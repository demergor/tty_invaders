#include <gtest/gtest.h>
#include <numeric>
#include <string_view>
#include <vector>

#include "tty_invaders/io/term.h"
#include "tty_invaders/rendering/formatting.h"

namespace tty_invaders::rendering {
TEST(FormattingTests, AnsiEscapeOmitsObsoleteEscapeSequences) {
  const auto char_count {[](const auto& inter, const auto& cur) {
    return inter + cur.size();
  }};

  Formatting prev {Formatting::BgGreen | Formatting::BrightYellow};
  Formatting prev_superset {
    Formatting::BgGreen | Formatting::BrightGreen | Formatting::Red
    | Formatting::BrightYellow
  };
  std::vector<std::string_view> prev_prev_superset_expected {
    io::term::bright_green,
    io::term::red
  };

  std::string prev_prev_superset_actual {ansi_escape(prev, prev_superset)};
  ASSERT_EQ(
    prev_prev_superset_actual.size(),
    std::accumulate(
      prev_prev_superset_expected.begin(),
      prev_prev_superset_expected.end(),
      0u,
      char_count
    )
  );

  for (const auto& formatting_str : prev_prev_superset_expected) {
    ASSERT_TRUE(prev_prev_superset_actual.contains(formatting_str));
  }

  Formatting not_prev_superset {
    Formatting::BgGreen | Formatting::BrightGreen | Formatting::Red | Formatting::Grey
  };

  std::vector<std::string_view> prev_not_prev_superset_expected {
    io::term::reset,
    io::term::bg_green,
    io::term::bright_green,
    io::term::red,
    io::term::grey
  };

  std::string prev_not_prev_superset_actual {ansi_escape(prev, not_prev_superset)};
  ASSERT_EQ(
    prev_not_prev_superset_actual.size(),
    std::accumulate(
      prev_not_prev_superset_expected.begin(),
      prev_not_prev_superset_expected.end(),
      0u,
      char_count
    )
  );

  for (const auto& formatting_str : prev_not_prev_superset_expected) {
    ASSERT_TRUE(prev_not_prev_superset_actual.contains(formatting_str));
  }

  Formatting prev_subset {Formatting::BrightYellow};
  std::vector<std::string_view> prev_prev_subset_expected {
    io::term::reset,
    io::term::bright_yellow
  };

  std::string prev_prev_subset_actual {ansi_escape(prev, prev_subset)};
  ASSERT_EQ(
    prev_not_prev_superset_actual.size(),
    std::accumulate(
      prev_not_prev_superset_expected.begin(),
      prev_not_prev_superset_expected.end(),
      0u,
      char_count
    )
  );

  for (const auto& formatting_str : prev_not_prev_superset_expected) {
    ASSERT_TRUE(prev_not_prev_superset_actual.contains(formatting_str));
  }
}
} // namespace tty_invaders::rendering
