#ifndef CONFIG_HPP
#define CONFIG_HPP

namespace nbody {
inline constexpr double G{6.67430e-11};
inline constexpr double c{299792.458};
struct parameters
{
  const double dt{0.001};
};
} // namespace nbody

#endif