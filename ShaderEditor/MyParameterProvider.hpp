#pragma once

#include <Engine/Data/RenderParameters.hpp>


using ShaderConfigType = std::vector<std::pair<Ra::Engine::Data::ShaderType, std::string>> ;

class MyParameterProvider : public Ra::Engine::Data::ShaderParameterProvider
{
  public:
    MyParameterProvider() {}
    ~MyParameterProvider() {}
    void updateGL() override {
        // Method called before drawing each frame in Renderer::updateRenderObjectsInternal.
        // The name of the parameter corresponds to the shader's uniform name.
        auto& renderParameters = getParameters();
        renderParameters.addParameter( "aColorUniform", m_colorParameter );
        renderParameters.addParameter( "aScalarUniform", m_scalarParameter );
    }
    void setOrComputeTheParameterValues() {
        // client side computation of the parameters, e.g.
        m_colorParameter  = Ra::Core::Utils::Color::Red();
        m_scalarParameter = .5_ra;
    }

  private:
    Ra::Core::Utils::Color m_colorParameter {Ra::Core::Utils::Color::Green()};
    Scalar m_scalarParameter {1};
};

