#pragma once

#include <Engine/Renderer/RenderTechnique/RenderParameters.hpp>
#include <Core/Utils/Color.hpp>


// 1. Implement a parameter provider to provide the uniforms for the shader
class MyParameterProvider : public Ra::Engine::ShaderParameterProvider {
public:
  MyParameterProvider() {}
  ~MyParameterProvider() {}
  void updateGL() override {
    // Method called before drawing each frame in Renderer::updateRenderObjectsInternal.
    // The name of the parameter corresponds to the shader's uniform name.
    m_renderParameters.addParameter( "aColorUniform", m_colorParameter );
    m_renderParameters.addParameter( "aScalarUniform", m_scalarParameter );
  }
  void setOrComputeTheParameterValues() {
    // client side computation of the parameters, e.g.
    m_colorParameter = Ra::Core::Utils::Color::Red();
    m_scalarParameter = .5_ra;
  }
private:
  Ra::Core::Utils::Color m_colorParameter;
  Scalar m_scalarParameter;
};

// 2. Implement a specific vertex and fragment shaders to compute the fragment color based on uniform values
// Vertex shader source code
const std::string vertexShaderSource{
    "#include \"TransformStructs.glsl\"\n"
    "layout (location = 0) in vec3 in_position;\n"
    "layout (location = 0) out vec3 out_pos;\n"
    "uniform Transform transform;\n"
    "void main(void)\n"
    "{\n"
    "    mat4 mvp    = transform.proj * transform.view;\n"
    "    out_pos     = in_position;\n"
    "    gl_Position = mvp*vec4(in_position.xyz, 1.0);\n"
    "}\n"};
// Fragment shader source code
const std::string fragmentShaderSource{
    "layout (location = 0) in  vec3 in_pos;\n"
    "layout (location = 0) out vec4 out_color;\n"
     "uniform vec4 aColorUniform;\n"
     "uniform float aScalarUniform;\n"
    "void main(void)\n"
    "{\n"
    "    out_color =  vec4(in_pos,1.)*aScalarUniform;\n"
    "}\n"};
