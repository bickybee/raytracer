#ifndef INTERVAL_H
#define INTERVAL_H

#include <limits>

const double infinity = std::numeric_limits<double>::infinity();

class interval {
  public:
    double min, max;

    interval() : min(+infinity), max(-infinity) {}

    interval(double _min, double _max) : min(_min), max(_max) {}

    bool contains(double x) const {
      return min <= x && x <= max;
    }

    bool surrounds(double x) const {
      return min < x && x < max;
    }
};

const static interval empty (+infinity, -infinity);
const static interval universe(-infinity, +infinity);

#endif