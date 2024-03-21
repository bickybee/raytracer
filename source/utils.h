#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <memory> // Shared pointers...

// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double pi = 3.1415926535897932385;

// Utility functions

inline double deg_to_rad(double deg) {
  return deg * pi / 180.0;
}

// Common headers

#include "interval.h"
#include "ray.h"
#include "vec3.h"

#endif