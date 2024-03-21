#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hittable_list : public hittable {
  public:
  // Shared_ptr => uses ref-counts!!! yay
    std::vector<shared_ptr<hittable>> objects;

    hittable_list() {}
    hittable_list(shared_ptr<hittable> object) { add(object); }

    void clear() {
      objects.clear();
    }

    void add(shared_ptr<hittable> object) {
      objects.push_back(object);
    }

    bool raycast(const ray &r, double tmin, double tmax, hit_record &hit) const override {
      hit_record test_hit;
      bool did_hit = false;
      double nearest_dist = tmax;

      for(const auto &obj : objects) {
        if (obj->raycast(r, tmin, tmax, test_hit) && test_hit.t < nearest_dist) {
          did_hit = true;
          nearest_dist = test_hit.t;
          hit = test_hit;
        }
      }

      return did_hit;
    }
};

#endif