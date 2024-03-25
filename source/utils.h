#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory> // Shared pointers...

// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double pi = 3.1415926535897932385;
const double infinity = std::numeric_limits<double>::infinity();

// Utility functions

inline double deg_to_rad(double deg) {
  return deg * pi / 180.0;
}

inline double random_double() {
  // Random real in [0,1).
  return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
  // Random real in [min,max).
  return min + (max - min) * random_double();
}

// Common headers

#include "interval.h"
#include "ray.h"
#include "vec3.h"

#endif