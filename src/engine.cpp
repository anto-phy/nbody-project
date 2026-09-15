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

  // Tamed light intensity so specular reflections don't wash colors to white
  _shader = Magnum::Shaders::PhongGL{};
  _shader.setLightPositions({{0.0f, 200.0f, 200.0f, 1.0f}})
      .setLightColors({Magnum::Color3{1.0f, 0.98f, 0.9f}});

  Magnum::GL::defaultFramebuffer.clearColor(
      Magnum::Color4{0.01f, 0.01f, 0.02f, 1.0f});

  // Load system (e.g. KeplerianDisk or solar_system)
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
  float x = static_cast<float>(body.get_position().x * _visualScale);
  float y = static_cast<float>(body.get_position().y * _visualScale);
  float z = static_cast<float>(body.get_position().z * _visualScale);

  float radius = static_cast<float>(body.get_radius() * _visualScale * 50.0);
  radius       = Magnum::Math::max(radius, 1.f);

  Magnum::Matrix4 model = Magnum::Matrix4::translation({x, y, z})
                        * Magnum::Matrix4::scaling(Magnum::Vector3{radius});

  Magnum::Matrix4 transformation = camera * model;

  Magnum::Color4 bodyColor;

  // Central star / massive body check
  if (body.get_mass() > 1.0e29) {
    bodyColor = Magnum::Color4{1.0f, 0.85f, 0.2f, 1.0f}; // Bright Yellow/Gold
  } else {
    // Dynamic color gradient based on velocity norm (Cool Blue -> Fast
    // Orange/Red)
    float speed  = static_cast<float>(body.get_velocity().norm());
    float factor = Magnum::Math::clamp(speed / 45000.0f, 0.0f, 1.0f);

    Magnum::Color4 slowColor{0.2f, 0.6f, 1.0f, 1.0f}; // Cyan/Blue
    Magnum::Color4 fastColor{1.0f, 0.3f, 0.1f, 1.0f}; // Red/Orange

    bodyColor = Magnum::Math::lerp(slowColor, fastColor, factor);
  }

  // Set ambient color matching body color so unlit sides don't render gray
  _shader.setProjectionMatrix(projection)
      .setTransformationMatrix(transformation)
      .setNormalMatrix(transformation.normalMatrix())
      .setAmbientColor(bodyColor.rgb() * 0.35f)
      .setDiffuseColor(bodyColor)
      .setSpecularColor(Magnum::Color4{0.2f, 0.2f, 0.2f, 1.0f});

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