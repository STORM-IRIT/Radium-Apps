#pragma once

#include <string>

#include <Engine/Component/GeometryComponent.hpp>
#include <Engine/Renderer/RenderTechnique/RenderParameters.hpp>
#include <Engine/Renderer/RenderTechnique/ShaderConfiguration.hpp> 
#include <Engine/Renderer/RenderTechnique/ShaderConfigFactory.hpp>
#include <Engine/Renderer/RenderObject/RenderObject.hpp>
#include <Engine/Renderer/RenderObject/RenderObjectManager.hpp>



/**
 * Helper component allowing to add a custom shader to an existing object.
 * 
 * The custom object must already habve a GeometryComponent to get access to the RenderObject.
 * The material is set when calling initialize.
 */
class CustomShaderComponent : public Ra::Engine::Component
{
  public:
    inline CustomShaderComponent( const std::string& name, 
                           Ra::Engine::Entity* entity,

                           Ra::Engine::GeometryComponent* geoComp,

                           std::shared_ptr<Ra::Engine::ShaderParameterProvider> parameterProvider,
                           const std::string& vertexShaderSource,
                           const std::string& fragmentShaderSource) :
        Ra::Engine::Component( name, entity ), 
        _geoComp(geoComp),
        _parameterProvider(parameterProvider), 
        _vertexShaderSource(vertexShaderSource),
        _fragmentShaderSource(fragmentShaderSource) { }
    ~CustomShaderComponent() override {}

    inline void initialize() override {
        // 3. Setup a Ra::Engine::ShaderConfiguration that uses these shaders
        Ra::Engine::ShaderConfiguration myConfig{getName()};
        myConfig.addShaderSource( Ra::Engine::ShaderType::ShaderType_VERTEX, _vertexShaderSource );
        myConfig.addShaderSource( Ra::Engine::ShaderType::ShaderType_FRAGMENT, _fragmentShaderSource );
        Ra::Engine::ShaderConfigurationFactory::addConfiguration( myConfig );

        // 4. Build a render technique that use this configuration
        auto renderTechnique = Ra::Core::make_shared<Ra::Engine::RenderTechnique>();
        renderTechnique->setConfiguration( myConfig, Ra::Engine::DefaultRenderingPasses::LIGHTING_OPAQUE );

        // 5. Create and associate the parameter provider with the RenderTechnique
        renderTechnique->setParametersProvider(_parameterProvider);

        // 6. Associate the render technique with a geometry in a Ra::Engine::RenderObject
        auto ro    = Ra::Engine::RadiumEngine::getInstance()->getRenderObjectManager()->getRenderObject(
            _geoComp->m_renderObjects[0]);
        ro->setRenderTechnique( renderTechnique );
    }

    private:
        Ra::Engine::GeometryComponent* _geoComp;
        std::shared_ptr<Ra::Engine::ShaderParameterProvider> _parameterProvider;
        const std::string& _vertexShaderSource, _fragmentShaderSource;
};
