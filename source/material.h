#ifndef MATERIAL_H
#define MATERIAL_H

#include "utils.h"

class hit_record;

class material {
  public:
    virtual ~material() = default;

    virtual bool scatter(
      const ray& r_in, const hit_record& hit, colour& attenuation, ray& scattered) const = 0;
};

class lambertian : public material {
  public:
    lambertian(const colour& a) : albedo(a) {}

    bool scatter(const ray& r_in, const hit_record& hit, colour& attenuation, ray& scattered) const override {
      // Lambertian model = most likely to bounce in dir of normal
      // Simplification choices: always scattering, fixed attenuation.
      vec3 scatter_dir = hit.normal + random_unit_vector();
      if (scatter_dir.near_zero())
        scatter_dir = hit.normal;

      scattered = ray(hit.point, scatter_dir);
      attenuation = albedo;
      return true;
    }
  private:
    colour albedo;
};

#endif