#include "tty_invaders/entities/defender.h"

#include <stdexcept>
#include "tty_invaders/io/key_press.h"
#include "tty_invaders/rendering/term_dims.h"

namespace tty_invaders::entities {
Defender::Defender(templates::ShipBody* body, const int armor, const int lives)
    : body {body}
    , armor {armor}
    , lives {lives} {
  if (lives <= 0) {
    throw std::runtime_error(
      "Error initializing defender: "
      "Amount of lives must be greater 0!"
    );
  }
}

void Defender::move(const io::KeyPress& kp, const rendering::TermDims& bounds) {
  if (kp.type == io::KeyPress::Type::None) {
    return;
  }

  // TODO: Figure out how to handle movements into enemy entities
  // TODO: Movement logic
}
} // namespace tty_invaders::entities
