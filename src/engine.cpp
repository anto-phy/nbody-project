#include "engine.hpp"
#include "simulation.hpp"

#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Math/Matrix4.h>
#include <Magnum/MeshTools/Compile.h>
#include <Magnum/Primitives/Icosphere.h>

namespace nbody {

Engine::Engine(const Arguments& arguments)
    : Magnum::Platform::Application{
          arguments, Configuration{}.setTitle("N-Body Physical Simulation")}
{
  Magnum::GL::Renderer::enable(Magnum::GL::Renderer::Feature::DepthTest);
  Magnum::GL::Renderer::enable(Magnum::GL::Renderer::Feature::FaceCulling);

  _sphereMesh =
      Magnum::MeshTools::compile(Magnum::Primitives::icosphereSolid(3));

  // Configurazione Shader PhongGL
  _shader = Magnum::Shaders::PhongGL{};
  _shader.setLightPositions({{0.0f, 0.0f, 0.0f, 1.0f}})
      .setLightColors({Magnum::Color3{1.0f, 0.95f, 0.8f} * 3.0f})
      .setAmbientColor(Magnum::Color3{0.05f});

  // Inizializzazione corpi fisici[cite: 8]
  _bodies.push_back(Body(1.989e30, 6.96e8, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}));
  _bodies.push_back(
      Body(5.972e24, 6.37e6, {1.496e11, 0, 0}, {0, 29780, 0}, {0, 0, 0}));
}

void Engine::render_body(const Body& body, const Magnum::Matrix4& projection,
                         const Magnum::Matrix4& camera)
{
  float x      = static_cast<float>(body.get_position().x * _visualScale);
  float y      = static_cast<float>(body.get_position().y * _visualScale);
  float z      = static_cast<float>(body.get_position().z * _visualScale);
  float radius = static_cast<float>(body.get_radius() * _visualScale * 50.0);

  Magnum::Matrix4 transformation =
      Magnum::Matrix4::translation({x, y, z})
      * Magnum::Matrix4::scaling(Magnum::Vector3{radius});

  _shader.setTransformationMatrix(transformation)
      .setNormalMatrix(transformation.normalMatrix())
      .setProjectionMatrix(projection)
      .setCameraMatrix(camera)
      .setDiffuseColor(Magnum::Color4{0.2f, 0.6f, 1.0f, 1.0f});

  _shader.draw(_sphereMesh);
}

void Engine::drawEvent()
{
  Magnum::GL::defaultFramebuffer.clear(Magnum::GL::FramebufferClear::Color
                                       | Magnum::GL::FramebufferClear::Depth);

  // 1. Calcolo dello stato fisico successivo (gestisce aggiunte/rimozioni di
  // corpi)[cite: 10]
  nbody::update_physics(_bodies, _params);

  // 2. Preparazione matrici di vista
  Magnum::Matrix4 projection = Magnum::Matrix4::perspectiveProjection(
      Magnum::Deg(60.0f), Magnum::Vector2{windowSize()}.aspectRatio(), 0.1f,
      1000.0f);
  Magnum::Matrix4 camera =
      Magnum::Matrix4::translation(Magnum::Vector3::zAxis(-300.0f));

  // 3. Rendering dinamico di ogni entità
  for (const auto& body : _bodies) {
    render_body(body, projection, camera);
  }

  swapBuffers();
  redraw();
}

} // namespace nbody