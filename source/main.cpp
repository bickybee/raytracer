#include "utils.h"

#include "colour.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

#include <iostream>

colour lerp_colour(const colour &start, const colour &end, const double progress) {
  return (1.0 - progress) * start + progress * end;
}

colour ray_colour(const ray &r, const hittable &world) {
  hit_record hit;
  if (world.raycast(r, 0, 100, hit)) {
    // Colour = normal, remapped from -1 to 1 -> 0 - 1
    return 0.5 * (hit.normal + colour(1,1,1));
  }

  vec3 unit_dir = normalized(r.direction());
  double progress = 0.5 * (unit_dir.y() + 1.0);
  return lerp_colour(colour(1,1,1), colour(0.3,0.4,0.9), progress);
}

int main() {

  // Image size based on desired aspect ratio.

  double desired_aspect_ratio = 16.0 / 8.0; 
  int image_w = 600;

  int image_h = static_cast<int>(image_w / desired_aspect_ratio);
  image_h = (image_h < 1) ? 1 : image_h; // Make sure height is at least 1.

  // Camera based on real aspect ratio.

  double real_aspect_ratio = (static_cast<double>(image_w)/image_h);
  double viewport_h = 2.0;
  double viewport_w = viewport_h * real_aspect_ratio;

  double focal_length = 1.0; // Distance from eye to viewport.
  point3 camera_center = point3(0,0,0);

  // Define viewport edges (world units?)

  vec3 viewport_u = vec3(viewport_w, 0, 0);
  vec3 viewport_v = vec3(0,-viewport_h, 0);

  // Define space between pixels, in viewport (world?) units.

  vec3 pixel_delta_u = viewport_u / image_w;
  vec3 pixel_delta_v = viewport_v / image_h;

  // Calculate upper left pixel position, in viewport (world?) units.

  point3 viewport_upper_left = camera_center + vec3(0, 0, -focal_length) - viewport_u/2.0 - viewport_v/2.0;
  point3 pixel_origin = viewport_upper_left + pixel_delta_u/2 + pixel_delta_v/2;

  // Create the world!

  hittable_list world;
  world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
  world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

  // Output part 1: color format, num cols, num rows, max color.

  std::cout << "P3\n" << image_w << ' ' << image_h << "\n255\n";

  // Output part 2: RBG triplets

  for (int j = 0; j < image_h; ++j) // scan top --> bottom
  {
    std::clog << "\rScanlines remaining: " << (image_h - j) << ' ' << std::flush;
    for (int i = 0; i < image_w; ++i) // scan left --> right
    {
      point3 pixel_pos = pixel_origin + i * pixel_delta_u + j * pixel_delta_v;
      vec3 ray_dir = pixel_pos - camera_center;
      ray ray(camera_center, ray_dir);

      colour found_colour = ray_colour(ray, world);
      write_colour(std::cout, found_colour);
    }
  }

  std::clog << "\rDone!                  \n";
};