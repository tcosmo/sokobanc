#include "misc.h"

uint8_t set_flag(uint8_t target, uint8_t flag, bool set) {
  if (!set) {
    if (target & flag) return target ^ flag;
    return target;
  }

  return target | flag;
}