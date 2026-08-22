#include "tty_invaders/gameplay/collision_handler.h"

#include <cassert>

#include "tty_invaders/effects/collision_effect.h"
#include "tty_invaders/effects/status_effect.h"
#include "tty_invaders/entities/defender.h"
#include "tty_invaders/entities/entity_type.h"
#include "tty_invaders/entities/invaders.h"
#include "tty_invaders/opts/game_settings.h"

namespace tty_invaders::gameplay {
void CollisionHandler::handle_collisions(
  entities::Defender& defender,
  entities::Invaders& invaders
) {
  for (const auto& collision : collisions) {
    if (
      entities::intersects(
        collision.target,
        entities::EntityType::Invader | entities::EntityType::InvaderBoss
      )
    ) {
      if (collision.effect.type != effects::CollisionEffect::Effect::Damage) {
        assert(false && "Invader mustn't be affected by anything other than damage!");
        continue;
      }

      invaders.armor[collision.target_id] -= collision.effect.val;
      continue;
    }

    if (collision.target != entities::EntityType::Defender) {
      assert(false && "CollisionData mustn't have a non-entity target!");
      continue;
    }

    switch (collision.effect.type) {
      case effects::CollisionEffect::Effect::Damage: {
        if (defender.effect == effects::StatusEffect::Invincible) {
          break;
        }
        defender.armor -= collision.effect.val;
        break;
      }
      case effects::CollisionEffect::Effect::Heal:
        defender.lives += collision.effect.val;
        break;
      case effects::CollisionEffect::Effect::Armor:
        defender.armor += collision.effect.val;
        break;
      case effects::CollisionEffect::Effect::PowerUp:
        defender.effect = static_cast<effects::StatusEffect>(collision.effect.val);
        defender.effect_duration = opts::game_settings::status_effect_duration;
        break;
    }
  }

  collisions.clear();
}
} // namespace tty_invaders::gameplay
