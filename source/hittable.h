#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class hit_record {
  public:
    double t; // How far along the original ray is the hit.
    point3 point; // Actual location of the hit.

    vec3 normal;
    bool front_face;
    
    // Calculate normal direction with outward-facing convention.
    // Can be determined during geometry intersection (here) or coloring => preference/context.
    void set_normal(const ray &r, const vec3& unit_normal) {
      front_face = dot(r.direction(), unit_normal) < 0;
      normal = front_face ? unit_normal : -unit_normal;
    }
};

class hittable {
  public:
    // Useful when deleting instance of derived through pointer to base.
    // The static type must have a virtual destructor or the behaviour is undefined!!
    // https://stackoverflow.com/questions/461203/when-to-use-virtual-destructors
    virtual ~hittable() = default; // use c++ default
    
    // "= 0" means no default implementation.
    virtual bool raycast(const ray &r, interval range, hit_record &hit) const = 0;
};

#endif