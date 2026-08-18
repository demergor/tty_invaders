#ifndef TTY_INVADERS_UTILITY_MASK_H
#define TTY_INVADERS_UTILITY_MASK_H

namespace tty_invaders::utility::mask {
template <typename Mask>
constexpr bool is_subset(Mask subset, Mask superset) {
  return (superset & subset) == subset;
}
} // namespace tty_invaders::utility::mask

#endif // TTY_INVADERS_UTILITY_MASK_H
