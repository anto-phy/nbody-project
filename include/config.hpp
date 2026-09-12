#ifndef CONFIG_HPP
#define CONFIG_HPP

namespace nbody {

inline constexpr double G{6.67430e-11};
inline constexpr double c{299792.458};

struct Parameters
{
  const double dt{0.001};
  const double epsilon{1.e-12};
};

} // namespace nbody

#endif