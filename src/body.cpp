#include "body.hpp"
#include "config.hpp"
#include <numeric>
#include <vector>

namespace nbody {

Vector3D<double> const& Body::get_position() const
{
  return pos_;
}

Vector3D<double> const& Body::get_velocity() const
{
  return vel_;
}

Vector3D<double> const& Body::get_acceleration() const
{
  return acc_;
}

double Body::get_mass() const
{
  return mass_;
}

double Body::get_radius() const
{
  return rad_;
}

Vector3D<double> Body::compute_position(std::vector<Body> const& universe,
                                        Parameters const& par) const
{
  return pos_ + vel_ * par.dt + 0.5 * acc_ * par.dt * par.dt;
}

Vector3D<double>
Body::compute_velocity(Vector3D<double> const& new_acceleration,
                       Parameters const& par) const
{
  return vel_ + 0.5 * (acc_ + new_acceleration) * par.dt;
}

Vector3D<double> Body::compute_acceleration(std::vector<Body> const& universe,
                                            Parameters const& par) const
{
  return std::accumulate(
      universe.begin(), universe.end(), Vector3D<double>{0., 0., 0.},
      [&, this](Vector3D<double> acc, const Body& other) {
        if (&other != this) {
          Vector3D<double> dr{other.pos_ - pos_};
          double r2{dr.norm2()};
          double factor{G * other.mass_
                        / std::pow(r2 + par.epsilon * par.epsilon, 1.5)};

          return acc + factor * dr;
        }

        return acc;
      });
}

Body Body::update(std::vector<Body> const& universe, Parameters const& par)
{
  Body next_state{*this};
  next_state.acc_ = compute_acceleration(universe, par);
  next_state.vel_ = compute_velocity(next_state.acc_, par);
  next_state.pos_ = compute_position(universe, par);
  return next_state;
}
} // namespace nbody