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
 public:
  explicit Engine(const Arguments& arguments);

 private:
  void drawEvent() override;

  // Funzione helper per il rendering del singolo corpo
  void render_body(const Body& body, const Magnum::Matrix4& projection,
                   const Magnum::Matrix4& camera);

  Magnum::GL::Mesh _sphereMesh;
  Magnum::Shaders::PhongGL _shader; // Usa PhongGL
  std::vector<Body> _bodies;
  Parameters _params;
  double _visualScale{1.0e-9};
};

} // namespace nbody

#endif