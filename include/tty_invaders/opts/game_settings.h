#ifndef TTY_INVADERS_OPTS_GAME_SETTINGS_H
#define TTY_INVADERS_OPTS_GAME_SETTINGS_H

#include <array>
#include <chrono>
#include <random>

#include "tty_invaders/entities/entity_type.h"

namespace tty_invaders::opts::game_settings {
constexpr char quit_key {'q'};

namespace movement {
constexpr char up {'w'};
constexpr char down {'s'};
constexpr char right {'d'};
constexpr char left {'a'};
} // namespace movement

constexpr char heart {'@'};

constexpr double high_percentage {100.0};
constexpr double mid_percentage {70.0};
constexpr double low_percentage {30.0};
constexpr double power_up_drop_chance {low_percentage};

constexpr int defender_lives {3};
constexpr int defender_armor {100};
constexpr int defender_atk_freq {10};
constexpr int defender_atk_dmg {25};

constexpr std::random_device::result_type invader_level_seed {0};
constexpr int invader_atk_freq {70};
constexpr int invader_atk_dmg {5};
constexpr int invader_armor {100};

constexpr int defender_mov_spd {1};

constexpr int action_bar_height {2};

constexpr std::chrono::milliseconds status_effect_duration {10'000};
constexpr std::chrono::milliseconds tick_rate {50};

constexpr std::array entity_type_priority {
  entities::EntityType::PowerUp,
  entities::EntityType::Explosion,
  entities::EntityType::InvaderBoss,
  entities::EntityType::Defender,
  entities::EntityType::Invader,
  entities::EntityType::InvaderBullet,
  entities::EntityType::DefenderBullet,
  entities::EntityType::None,
};
} // namespace tty_invaders::opts::game_settings

#endif // TTY_INVADERS_OPTS_GAME_SETTINGS_H
