#include "engine.hpp"
#include "generator.hpp"
#include "simulation.hpp"

#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Math/Functions.h>
#include <Magnum/Math/Matrix4.h>
#include <Magnum/MeshTools/Compile.h>
#include <Magnum/Primitives/Icosphere.h>
#include <Magnum/Trade/MeshData.h>

namespace nbody {

Engine::Engine(const Arguments& arguments)
    : Magnum::Platform::Application{
          arguments, Configuration{}.setTitle("N-Body Physical Simulation")}
{
  Magnum::GL::Renderer::enable(Magnum::GL::Renderer::Feature::DepthTest);
  Magnum::GL::Renderer::enable(Magnum::GL::Renderer::Feature::FaceCulling);

  _sphereMesh =
      Magnum::MeshTools::compile(Magnum::Primitives::icosphereSolid(3));

  _shader = Magnum::Shaders::PhongGL{};
  _shader.setLightPositions({{0.0f, 100.0f, 100.0f, 1.0f}})
      .setLightColors({Magnum::Color3{1.0f, 0.95f, 0.8f} * 3.0f})
      .setAmbientColor(Magnum::Color3{0.2f});

  Magnum::GL::defaultFramebuffer.clearColor(
      Magnum::Color4{0.02f, 0.02f, 0.04f, 1.0f});

  // Load generated system
  _bodies = SystemGenerator::solar_system();
}

void Engine::mousePressEvent(MouseEvent& event)
{
  if (event.button() == MouseEvent::Button::Left) {
    _lastMousePosition = event.position();
  }
}

void Engine::mouseMoveEvent(MouseMoveEvent& event)
{
  if (event.buttons() & MouseMoveEvent::Button::Left) {
    Magnum::Vector2i delta = event.position() - _lastMousePosition;

    _cameraYaw += delta.x() * 0.5f;
    _cameraPitch += delta.y() * 0.5f;

    // Clamp pitch to prevent camera flipping upside down
    _cameraPitch = Magnum::Math::clamp(_cameraPitch, -89.0f, 89.0f);

    _lastMousePosition = event.position();
    redraw();
  }
}

void Engine::mouseScrollEvent(MouseScrollEvent& event)
{
  if (event.offset().y() != 0) {
    // Scroll up = Zoom in, Scroll down = Zoom out
    _cameraRadius -= event.offset().y() * 20.0f;
    _cameraRadius = Magnum::Math::max(5.0f, _cameraRadius);
    redraw();
  }
}

void Engine::render_body(const Body& body, const Magnum::Matrix4& projection,
                         const Magnum::Matrix4& camera)
{
  float x      = static_cast<float>(body.get_position().x * _visualScale);
  float y      = static_cast<float>(body.get_position().y * _visualScale);
  float z      = static_cast<float>(body.get_position().z * _visualScale);
  // Exaggerate small bodies so planets remain visible at solar-system scale.
  float radius = static_cast<float>(body.get_radius() * _visualScale * 50.0);
  radius = Magnum::Math::max(radius, 2.0f);

  Magnum::Matrix4 model = Magnum::Matrix4::translation({x, y, z})
                        * Magnum::Matrix4::scaling(Magnum::Vector3{radius});

  Magnum::Matrix4 transformation = camera * model;

  _shader.setProjectionMatrix(projection)
      .setTransformationMatrix(transformation)
      .setNormalMatrix(transformation.normalMatrix())
      .setDiffuseColor(Magnum::Color4{0.2f, 0.6f, 1.0f, 1.0f});

  _shader.draw(_sphereMesh);
}

void Engine::drawEvent()
{
  Magnum::GL::defaultFramebuffer.clear(Magnum::GL::FramebufferClear::Color
                                       | Magnum::GL::FramebufferClear::Depth);

  nbody::update_physics(_bodies, _params);

  Magnum::Matrix4 projection = Magnum::Matrix4::perspectiveProjection(
      Magnum::Deg(60.0f), Magnum::Vector2{windowSize()}.aspectRatio(), 0.1f,
      5000.0f);

  // Compute orbit camera matrix using pitch, yaw, and zoom distance
  Magnum::Matrix4 camera =
      Magnum::Matrix4::translation(Magnum::Vector3::zAxis(-_cameraRadius))
      * Magnum::Matrix4::rotationX(Magnum::Deg(_cameraPitch))
      * Magnum::Matrix4::rotationY(Magnum::Deg(_cameraYaw));

  for (const auto& body : _bodies) {
    render_body(body, projection, camera);
  }

  swapBuffers();
  redraw();
}

} // namespace nbody