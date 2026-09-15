#include "generator.hpp"
#include <cmath>
#include <random>

namespace nbody {

std::vector<Body> SystemGenerator::solar_system()
{
  return {
      Body(1.989e30, 6.96e8, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}), // Sun
      Body(3.301e23, 2.439e6, {5.79e10, 0, 0}, {0, 47360, 0},
           {0, 0, 0}), // Mercury
      Body(4.867e24, 6.051e6, {1.082e11, 0, 0}, {0, 35020, 0},
           {0, 0, 0}), // Venus
      Body(5.972e24, 6.371e6, {1.496e11, 0, 0}, {0, 29780, 0},
           {0, 0, 0}), // Earth
      Body(6.417e23, 3.389e6, {2.279e11, 0, 0}, {0, 24070, 0},
           {0, 0, 0}) // Mars
  };
}

std::vector<Body> SystemGenerator::KeplerianDisk(size_t count,
                                                 double max_radius,
                                                 double central_mass)
{
  std::vector<Body> bodies;
  bodies.reserve(count + 1);

  // Central supermassive body
  bodies.emplace_back(central_mass, max_radius * 0.01,
                      Vector3D<double>{0, 0, 0}, Vector3D<double>{0, 0, 0},
                      Vector3D<double>{0, 0, 0});

  std::mt19937 rng(42);
  std::uniform_real_distribution<double> dist_r(max_radius * 0.05, max_radius);
  std::uniform_real_distribution<double> dist_theta(0.0, 2.0 * M_PI);

  for (size_t i = 0; i < count; ++i) {
    double r     = dist_r(rng);
    double theta = dist_theta(rng);

    double x = r * std::cos(theta);
    double y = r * std::sin(theta);

    // Compute tangential speed for stable circular orbit
    double v_mag = std::sqrt(G * central_mass / r);
    double vx    = -v_mag * std::sin(theta);
    double vy    = v_mag * std::cos(theta);

    bodies.emplace_back(1.0e22, max_radius * 0.002, Vector3D<double>{x, y, 0},
                        Vector3D<double>{vx, vy, 0}, Vector3D<double>{0, 0, 0});
  }

  return bodies;
}

} // namespace nbody