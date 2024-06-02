#include <termios.h>

speed_t
cfgetospeed(const struct termios *t) {
  return t->c_ospeed;
}
