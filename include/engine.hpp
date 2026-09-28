#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "body.hpp"
#include "config.hpp"

#include <Magnum/GL/Mesh.h>
#include <Magnum/Math/Matrix4.h>
#include <Magnum/Math/Vector2.h>
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

  // Mouse & Camera Event Handlers
  void mousePressEvent(MouseEvent& event) override;
  void mouseMoveEvent(MouseMoveEvent& event) override;
  void mouseScrollEvent(MouseScrollEvent& event) override;

  void render_body(const Body& body, const Magnum::Matrix4& projection,
                   const Magnum::Matrix4& camera);

  Magnum::GL::Mesh _sphereMesh;
  Magnum::Shaders::PhongGL _shader;
  std::vector<Body> _bodies;
  Parameters _params;
  double _visualScale{1.0e-9};

  // Orbit Camera State
  Magnum::Vector2i _lastMousePosition;
  float _cameraRadius{300.0f};
  float _cameraYaw{0.0f};
  float _cameraPitch{20.0f};
};

} // namespace nbody

#endif