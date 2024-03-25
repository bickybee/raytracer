#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable {
  private:
    point3 center;
    double radius;

  public:
    sphere(point3 _center, double _radius) : center(_center), radius(_radius) {}

    bool raycast(const ray &r, interval range, hit_record &hit) const override {
      // Solve quadratic formula... (simplified with half_b to reduce some operations)
      vec3 center_to_origin = r.origin() - center;
      double a = r.direction().length_squared();
      double half_b = dot(r.direction(), center_to_origin);
      double c = center_to_origin.length_squared() - radius * radius;

      // Discriminant = under the sqrt
      double discriminant = half_b * half_b - a * c;
      if (discriminant < 0) {
        return false;
      }
      
      // Find a root between tmin and tmax.
      double sqrt_d = sqrt(discriminant);
      double t = (-half_b - sqrt_d) / a; // Near root.
      if (!range.contains(t)) {
        t = (-half_b + sqrt_d) / a; // Far root.
        if (!range.contains(t)) {
          return false;
        }
      }

      hit.t = t;
      hit.point = r.at(t);

      // Naturally, the normal of a sphere at P is (P - center of sphere).
      // Also naturally, the length of this normal = r.
      // So, to get the unit length, we simply divide by r.
      vec3 unit_normal = (hit.point - center) / radius;
      hit.set_normal(r, unit_normal);
      return true;
    }

};

#endif