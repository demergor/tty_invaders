#include "tty_invaders/rendering/render_attr.h"

#include "tty_invaders/entities/entity_type.h"
#include "tty_invaders/rendering/formatting.h"

namespace tty_invaders::rendering {
RenderAttr::RenderAttr(entities::EntityType type) {
  switch (type) {
    case entities::EntityType::Defender:
      formatting = Formatting::Bold | Formatting::BrightGreen;
      ch = 'A';
      break;
    case entities::EntityType::DefenderBullet:
      formatting = Formatting::Green;
      ch = 'o';
      break;
    case entities::EntityType::Explosion:
      formatting = Formatting::BgRed;
      ch = ' ';
      break;
    case entities::EntityType::Invader:
      formatting = Formatting::None;
      ch = 'V';
      break;
    case entities::EntityType::InvaderBullet:
      formatting = Formatting::BrightRed | Formatting::Bold;
      ch = 'o';
      break;
    case entities::EntityType::PowerUp:
      formatting = Formatting::Blue;
      ch = '+';
      break;
    default:
      formatting = Formatting::None;
      ch = ' ';
      break;
  }
}
} // namespace tty_invaders::rendering
