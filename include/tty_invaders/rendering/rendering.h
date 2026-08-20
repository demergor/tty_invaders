#ifndef TTY_INVADERS_RENDERING_RENDERING_H
#define TTY_INVADERS_RENDERING_RENDERING_H

#include <cstddef>

#include "tty_invaders/entities/defender.h"
#include "tty_invaders/gameplay/collision_buffer.h"
#include "tty_invaders/geometry/rect_coords.h"
#include "tty_invaders/rendering/term_dims.h"

namespace tty_invaders::rendering {
constexpr std::size_t expected_render_bytes_per_cell {4};

void render_bar(const entities::Defender&, const TermDims&);
void render_main(const gameplay::CollisionBuffer&, const TermDims&);
// Determines the minimal area that needs to be touched to blit as little as possible
geometry::RectCoords dirty_area(const gameplay::CollisionBuffer&, const TermDims&);
} // namespace tty_invaders::rendering

#endif // TTY_INVADERS_RENDERING_RENDERING_H
