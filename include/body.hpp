#ifndef NBODY_BODY_HPP
#define NBODY_BODY_HPP

#include "vector3d.hpp"
#include <cmath>

namespace nbody {

class Body
{
 private:
  double mass_{1.e6};
  double rad_{1.e4};
  Vector3D<double> pos_{};
  Vector3D<double> vel_{};

 public:
  Body (double m, double r, Vector3D<double> p, Vector3D<double> v) : mass_{m}, rad_{r}, pos_{p}, vel_{v} {}


};

} // namespace nbody
#endif