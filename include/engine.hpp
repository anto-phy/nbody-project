#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "body.hpp"
#include "config.hpp"
#include <Magnum/GL/Mesh.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/Shaders/PbrMetallicRoughness.h>
#include <vector>

namespace nbody {

class Engine : public Magnum::Platform::Application
{
 public:
  explicit Engine(const Arguments& arguments);

 private:
  void drawEvent() override;

  Magnum::GL::Mesh _sphereMesh;
  Magnum::Shaders::PbrMetallicRoughness _pbrShader;
  std::vector<Body> _bodies;
  Parameters _params;
  double _visualScale{1.0e-9}; // Scales physical meters to rendering units
};

} // namespace nbody
#endif