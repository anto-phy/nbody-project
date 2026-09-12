#ifndef NBODY_BODY_HPP
#define NBODY_BODY_HPP

#include "config.hpp"
#include "vector3d.hpp"
#include <cmath>
#include <stdexcept>
#include <vector>

namespace nbody {

class Body
{
 private:
  double mass_{1.e6};
  double rad_{1.e4};
  Vector3D<double> pos_{};
  Vector3D<double> vel_{};
  Vector3D<double> acc_{};

 public:
  Body(double m, double r, Vector3D<double> p, Vector3D<double> v,
       Vector3D<double> a)
      : mass_{m}
      , rad_{r}
      , pos_{p}
      , vel_{v}
      , acc_{a}
  {
    if (m <= 0) {
      throw std::runtime_error(
          "Mass of a body can't be less or equal to zero.\n");
    }
    if (r <= 0) {
      throw std::runtime_error(
          "Radius of a body can't be less or equal to zero.\n");
    }
  }

  Vector3D<double> const& get_position() const;

  Vector3D<double> const& get_velocity() const;

  Vector3D<double> const& get_acceleration() const;

  double get_mass() const;

  double get_radius() const;

  Body update(std::vector<Body> const&, Parameters const&);

  Vector3D<double> compute_position(std::vector<Body> const&,
                                    Parameters const&) const;

  Vector3D<double> compute_velocity(Vector3D<double> const&,
                                    Parameters const&) const;

  Vector3D<double> compute_acceleration(std::vector<Body> const&,
                                        Parameters const&) const;
};

} // namespace nbody
#endif