#ifndef INCLUDES_H
#define INCLUDES_H

#include <array>
#include <string>
#include <iostream>
#include <vector>
#include <cassert>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <regex>
#include <cctype>
#include "vector.h"
#include "Direction.h"

using pos_t = uint8_t;

using position2d_t = vector2d<pos_t>;

using direction = Direction;

#endif
