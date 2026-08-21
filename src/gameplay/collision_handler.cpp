#include "tty_invaders/gameplay/collision_handler.h"

#include <algorithm>
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
  const auto dedup_end {deduplicate_collisions()};
  for (auto it {collisions.begin()}; it != dedup_end; ++it) {
    if (
      entities::intersects(
        it->target,
        entities::EntityType::Invader | entities::EntityType::InvaderBoss
      )
    ) {
      if (it->effect.type != effects::CollisionEffect::Effect::Damage) {
        assert(false && "Invader mustn't be affected by anything other than damage!");
        continue;
      }

      invaders.armor[it->target_id] -= it->effect.val;
      continue;
    }

    if (it->target != entities::EntityType::Defender) {
      assert(false && "CollisionData mustn't have a non-entity target!");
      continue;
    }

    switch (it->effect.type) {
      case effects::CollisionEffect::Effect::Damage:
        defender.armor -= it->effect.val;
        break;
      case effects::CollisionEffect::Effect::Heal:
        defender.lives += it->effect.val;
        break;
      case effects::CollisionEffect::Effect::Armor:
        defender.armor += it->effect.val;
        break;
      case effects::CollisionEffect::Effect::PowerUp:
        defender.effect = static_cast<effects::StatusEffect>(it->effect.val);
        defender.effect_duration = opts::game_settings::status_effect_duration;
        break;
    }
  }

  collisions.clear();
}

std::vector<CollisionData>::iterator CollisionHandler::deduplicate_collisions() {
  std::sort(
    collisions.begin(),
    collisions.end(),
    [](const auto& be_greater, const auto& be_less) {
      if (be_greater.target == be_less.target) {
        return be_greater.effect.val > be_less.effect.val;
      }

      return be_greater.target > be_less.target;
    }
  );

  return std::unique(
    collisions.begin(),
    collisions.end(),
    [](const auto& a, const auto& b) {
      return a.effect.type == b.effect.type && a.target == b.target
        && a.target_id == b.target_id;
    }
  );
}
} // namespace tty_invaders::gameplay
