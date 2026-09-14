#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "body.hpp"
#include "config.hpp"

#include <Magnum/GL/Mesh.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/Shaders/PhongGL.h>
#include <vector>

namespace nbody {

class Engine : public Magnum::Platform::Application
{
 private:
  void drawEvent() override;

  // helper per il rendering del singolo corpo
  void render_body(const Body& body, const Magnum::Matrix4& projection,
                   const Magnum::Matrix4& camera);

  Magnum::GL::Mesh _sphereMesh;
  Magnum::Shaders::PhongGL _shader;
  std::vector<Body> _bodies;
  Parameters _params;
  double _visualScale{1.0e-9};

 public:
  explicit Engine(const Arguments& arguments);
};

} // namespace nbody

#endif