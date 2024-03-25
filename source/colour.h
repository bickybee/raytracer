#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

using colour = vec3;

inline double linear_to_gamma(double linear_component) {
  return sqrt(linear_component);
}

void write_colour(std::ostream &out, colour pixel_colour, int samples_per_pixel) {

  double r = pixel_colour.x();
  double g = pixel_colour.y();
  double b = pixel_colour.z();

  // Divide colour by number of samples
  double scale = 1.0 / samples_per_pixel;
  r *= scale;
  g *= scale;
  b *= scale;

  // Apply the linear->gamma transformation
  r = linear_to_gamma(r);
  g = linear_to_gamma(g);
  b = linear_to_gamma(b);

  static const interval intensity(0.000, 0.999);
  out << static_cast<int>(256 * intensity.clamp(r)) << ' '
      << static_cast<int>(256 * intensity.clamp(g)) << ' '
      << static_cast<int>(256 * intensity.clamp(b)) << '\n';
}

colour lerp_colour(const colour &start, const colour& end, const double progress) {
  return (1.0 - progress) * start + progress * end;
}

#endif