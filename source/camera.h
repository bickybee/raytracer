#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"

#include "colour.h"
#include "hittable.h"

#include <iostream>

class camera {
  private:
    double target_aspect_ratio = 1.0;
    int image_w                = 100;
    int samples_per_pixel      = 10;

  public:
    camera(double aspect_ratio, int image_width, int samples_pp)
           : target_aspect_ratio(aspect_ratio), image_w(image_width), samples_per_pixel(samples_pp) {}
    camera() { }

    void render(const hittable &world) {
      init();

      // Output part 1: color format, num cols, num rows, max color.

      std::cout << "P3\n" << image_w << ' ' << image_h << "\n255\n";

      // Output part 2: RBG triplets

      for (int j = 0; j < image_h; ++j) // scan top --> bottom
      {
        std::clog << "\rScanlines remaining: " << (image_h - j) << ' ' << std::flush;
        for (int i = 0; i < image_w; ++i) // scan left --> right
        {
          colour pixel_colour(0, 0, 0);
          for (int sample = 0; sample < samples_per_pixel; ++sample) {
            ray r = get_ray(i, j);
            pixel_colour += ray_colour(r, world);
          }
          write_colour(std::cout, pixel_colour, samples_per_pixel);
        }
      }

      std::clog << "\rDone!                  \n";
    }
  
  private:
    int image_h;
    point3 camera_pos;
    point3 pixel_origin;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;

    void init() {
       // Image height based on desired aspect ratio + width.

      image_h = static_cast<int>(image_w / target_aspect_ratio);
      image_h = (image_h < 1) ? 1 : image_h; // Make sure height is at least 1.

      // Viewport based on real aspect ratio.

      double real_aspect_ratio = (static_cast<double>(image_w)/image_h);
      double viewport_h = 2.0;
      double viewport_w = viewport_h * real_aspect_ratio;

      double focal_length = 1.0; // Distance from eye to viewport.
      camera_pos = point3(0,0,0);

      // Define viewport edges (world units?)

      vec3 viewport_u = vec3(viewport_w, 0, 0);
      vec3 viewport_v = vec3(0,-viewport_h, 0);

      // Define space between pixels, in viewport (world?) units.

      pixel_delta_u = viewport_u / image_w;
      pixel_delta_v = viewport_v / image_h;

      // Calculate upper left pixel position, in viewport (world?) units.

      point3 viewport_upper_left = camera_pos + vec3(0, 0, -focal_length) - viewport_u/2.0 - viewport_v/2.0;
      pixel_origin = viewport_upper_left + pixel_delta_u/2 + pixel_delta_v/2;
    }

    ray get_ray(int i, int j) const {
      // Returns camera ray sample for pixel_i,j
      point3 pixel_pos = pixel_origin + i * pixel_delta_u + j * pixel_delta_v;
      point3 pixel_sample = pixel_pos + pixel_sample_square();

      vec3 ray_dir = pixel_sample - camera_pos;
      ray ray(camera_pos, ray_dir);

      return ray;
    }

    vec3 pixel_sample_square() const {
      // Returns random point in the square surrounding a pixel w.r.t. the origin
      // (from -0.5 to +0.5)
      double x = -0.5 + random_double();
      double y = -0.5 + random_double();
      return (x * pixel_delta_u) + (y * pixel_delta_v);
    }

    colour ray_colour(const ray &r, const hittable &world) const {
      hit_record hit;
      if (world.raycast(r, 0, 100, hit)) {
        // Colour = normal, remapped from -1 to 1 -> 0 - 1
        return 0.5 * (hit.normal + colour(1,1,1));
      }

      vec3 unit_dir = normalized(r.direction());
      double progress = 0.5 * (unit_dir.y() + 1.0);
      return lerp_colour(colour(1,1,1), colour(0.3,0.4,0.9), progress);
    }
};

#endif