#ifndef TTY_INVADERS_OPTS_GAME_SETTINGS_H
#define TTY_INVADERS_OPTS_GAME_SETTINGS_H

namespace tty_invaders::opts::game_settings {
constexpr int defender_lives {3};
constexpr int defender_armor {100};
constexpr int defender_atk_freq {10};

constexpr int invader_atk_freq {25};
constexpr int invader_atk_dmg {25};

constexpr int defender_mov_spd {1};

constexpr int action_bar_height {1};
}

#endif // TTY_INVADERS_OPTS_GAME_SETTINGS_H
