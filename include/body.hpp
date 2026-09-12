#ifndef NBODY_BODY_HPP
#define NBODY_BODY_HPP

#include "vector3d.hpp"
#include <cmath>
#include <vector>

namespace nbody {

class Body
{
 private:
  double mass_{1.e6};
  double rad_{1.e4};
  Vector3D<double> pos_{};
  Vector3D<double> vel_{};

 public:
  Body(double m, double r, Vector3D<double> p, Vector3D<double> v)
      : mass_{m}
      , rad_{r}
      , pos_{p}
      , vel_{v}
  {}

  Vector3D<double> const& get_position() const;

  Vector3D<double> const& get_velocity() const;

  Body update(std::vector<Body>, double dt);
};

} // namespace nbody
#endif