#ifndef TTY_INVADERS_RENDERING_RENDER_ATTR_H
#define TTY_INVADERS_RENDERING_RENDER_ATTR_H

#include "tty_invaders/rendering/formatting.h"

namespace tty_invaders::rendering {
struct RenderAttr {
  Formatting formatting;
  char ch;
};
} // namespace tty_invaders::rendering

#endif // TTY_INVADERS_RENDERING_RENDER_ATTR_H
