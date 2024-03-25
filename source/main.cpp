#include "utils.h"

#include "camera.h"
#include "colour.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

#include <iostream>

int main() {

  hittable_list world;
  shared_ptr<lambertian> green_diffuse = make_shared<lambertian>(lambertian(colour(0.2,0.5,0.2)));
  world.add(make_shared<sphere>(point3(0,0,-1), 0.5, green_diffuse));
  world.add(make_shared<sphere>(point3(0,-100.5,-1), 100, green_diffuse));

  camera cam = camera(16.0 / 9.0, 600, 100, 50);
  cam.render(world);
};