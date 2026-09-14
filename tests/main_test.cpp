#include "body.hpp"
#include <cassert>

int main()
{
  // Basic sanity check test
  nbody::Body test_body(1.0, 1.0, {0, 0, 0}, {0, 0, 0}, {0, 0, 0});
  assert(test_body.get_mass() == 1.0);
  return 0;
}