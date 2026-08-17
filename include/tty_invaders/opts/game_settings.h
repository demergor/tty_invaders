#ifndef TTY_INVADERS_OPTS_GAME_SETTINGS_H
#define TTY_INVADERS_OPTS_GAME_SETTINGS_H

namespace tty_invaders::opts::game_settings {
namespace movement {
constexpr char up {'w'};
constexpr char down {'s'};
constexpr char right {'d'};
constexpr char left {'a'};
} // namespace movement

constexpr int defender_lives {3};
constexpr int defender_armor {100};
constexpr int defender_atk_freq {10};
constexpr int defender_atk_dmg {100};

constexpr int invader_level_seed {0};
constexpr int invader_atk_freq {25};
constexpr int invader_atk_dmg {25};

constexpr int defender_mov_spd {1};

constexpr int action_bar_height {1};
} // namespace tty_invaders::opts::game_settings

#endif // TTY_INVADERS_OPTS_GAME_SETTINGS_H
