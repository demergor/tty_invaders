#ifndef TTY_INVADERS_UTILITY_CONTAINERS_H
#define TTY_INVADERS_UTILITY_CONTAINERS_H

namespace tty_invaders::utility {
template <typename T>
concept HasSize = requires(T t) { t.size(); };

template <HasSize Reference, HasSize... Tests>
bool sizes_match(const Reference& ref, const Tests&... tests) {
  return ((ref.size() == tests.size()) && ...);
}
} // namespace tty_invaders::utility

#endif // TTY_INVADERS_UTILITY_CONTAINERS_H
