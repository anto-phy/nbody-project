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
  // Enable core modern OpenGL features
  Magnum::GL::Renderer::enable(Magnum::GL::Renderer::Feature::DepthTest);
  Magnum::GL::Renderer::enable(Magnum::GL::Renderer::Feature::FaceCulling);

  // Compile 3D icosphere mesh for rendering bodies
  _sphereMesh =
      Magnum::MeshTools::compile(Magnum::Primitives::icosphereSolid(3));

  // Setup PBR shader and light source at the center
  _pbrShader = Magnum::Shaders::PbrMetallicRoughness{};
  _pbrShader.setLightPositions({{0.0f, 0.0f, 0.0f, 1.0f}})
      .setLightColors({Magnum::Color3{1.0f, 0.9f, 0.8f} * 5.0f});

  // Initialize simulation bodies using your constructor structure
  // Parameters struct provides dt and epsilon[cite: 6]
  _bodies.push_back(
      Body(1.989e30, 6.96e8, {0, 0, 0}, {0, 0, 0}, {0, 0, 0})); // Sun
  _bodies.push_back(Body(5.972e24, 6.37e6, {1.496e11, 0, 0}, {0, 29780, 0},
                         {0, 0, 0})); // Earth
}

void Engine::drawEvent()
{
  Magnum::GL::defaultFramebuffer.clear(Magnum::GL::FramebufferClear::Color
                                       | Magnum::GL::FramebufferClear::Depth);

  // Advance physics state using your Body::update logic[cite: 5, 9]
  std::vector<Body> next_universe;
  next_universe.reserve(_bodies.size());
  for (auto& body : _bodies) {
    next_universe.push_back(body.update(_bodies, _params));
  }
  _bodies = std::move(next_universe);

  // Set up projection and camera matrices
  Magnum::Matrix4 projection = Magnum::Matrix4::perspectiveProjection(
      Magnum::Deg(60.0f), Magnum::Vector2{windowSize()}.aspectRatio(), 0.1f,
      1000.0f);
  Magnum::Matrix4 camera =
      Magnum::Matrix4::translation(Magnum::Vector3::zAxis(-300.0f));

  _pbrShader.setProjectionMatrix(projection).setCameraMatrix(camera);
  // Render bodies
  for (const auto& body : _bodies) {
    // Note: Ensure get_position() and get_radius() public getters exist in your
    // Body class[cite: 5] float x = static_cast<float>(body.get_position().x *
    // _visualScale); float y = static_cast<float>(body.get_position().y *
    // _visualScale); float z = static_cast<float>(body.get_position().z *
    // _visualScale); float radius = static_cast<float>(body.get_radius() *
    // _visualScale * 50.0);

    // Magnum::Matrix4 transformation = Magnum::Matrix4::translation({x, y, z})
    // *
    //                                  Magnum::Matrix4::scaling(Magnum::Vector3{radius});

    // _pbrShader.setTransformationMatrix(transformation)
    //           .setNormalMatrix(transformation.normalMatrix())
    //           .setBaseColor(Magnum::Color4{0.2f, 0.6f, 1.0f, 1.0f})
    //           .setRoughness(0.5f)
    //           .setMetallic(0.1f);

    // _pbrShader.draw(_sphereMesh);
  }

  swapBuffers();
  redraw();
}

} // namespace nbody