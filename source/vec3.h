#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3 {
  private:
    double v[3];

  public:
    vec3() : v{0,0,0}{}
    vec3(double x, double y, double z) : v{x,y,z}{}

    double x() const { return v[0]; }
    double y() const { return v[1]; }
    double z() const { return v[2]; }

    vec3 operator-() const { return vec3(-v[0], -v[1], -v[2]); }
    double operator[](int i) const { return v[i]; }
    double& operator[](int i) { return v[i]; }

    // "+=" style operators are special, require returning the reference to the obj.
    vec3& operator+=(const vec3 &u) {
      v[0] += u.v[0];
      v[1] += u.v[1];
      v[2] += u.v[2];
      return *this;
    }

    vec3& operator-=(const vec3 &u) {
      v[0] -= u.v[0];
      v[1] -= u.v[1];
      v[2] -= u.v[2];
      return *this;
    }

    vec3& operator*=(double t) {
      v[0] *= t;
      v[1] *= t;
      v[2] *= t;
      return *this;
    }

    vec3& operator/=(double t) {
      v[0] /= t;
      v[1] /= t;
      v[2] /= t;
      return *this;
    }

    double length_squared() const {
      return v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
    }

    double length() const {
      return sqrt(length_squared());
    }
  };

  using point3 = vec3; // Useful alias.

  inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
  }

  inline vec3 operator+(const vec3 &a, const vec3 &b) {
    return vec3(a.x() + b.x(), a.y() + b.y(), a.z() + b.z());
  }

  inline vec3 operator-(const vec3 &a, const vec3 &b) {
    return vec3(a.x() - b.x(), a.y() - b.y(), a.z() - b.z());
  }

  inline vec3 operator*(const vec3 &a, const vec3 &b) {
    return vec3(a.x() * b.x(), a.y() * b.y(), a.z() * b.z());
  }

  inline vec3 operator/(const vec3 &a, const vec3 &b) {
    return vec3(a.x() / b.x(), a.y() / b.y(), a.z() / b.z());
  }

  inline vec3 operator*(double t, const vec3 &v) {
    return vec3(v.x()*t, v.y()*t, v.z()*t);
  }

  inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
  }

  inline vec3 operator/(const vec3 &v, double t) {
    return v * (1/t);
  }

  inline double dot(const vec3 &a, const vec3 &b) {
    return a.x() * b.x() + a.y() * b.y() + a.z() * b.z();
  }

  inline vec3 cross(const vec3 &a, const vec3 &b) {
    return vec3(a.y() * b.z() - a.z() * b.y(),
                a.z() * b.x() - a.x() * b.z(),
                a.x() * b.y() - a.y() * b.x());
  }

  inline vec3 normalized(const vec3 &v) {
    return v / v.length();
  }

#endif