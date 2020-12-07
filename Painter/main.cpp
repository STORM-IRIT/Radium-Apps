// Include Radium base application and its simple Gui
#include <GuiBase/BaseApplication.hpp>
#include <GuiBase/RadiumWindow/SimpleWindowFactory.hpp>

// include the Engine/entity/component interface
#include <Core/Geometry/MeshPrimitives.hpp>
#include <Engine/Component/GeometryComponent.hpp>
#include <Engine/Managers/EntityManager/EntityManager.hpp>
#include <Engine/System/GeometrySystem.hpp>
#include <Engine/Renderer/RenderTechnique/ShaderConfiguration.hpp> 
#include <Engine/Renderer/RenderTechnique/ShaderConfigFactory.hpp>
#include <Engine/Renderer/RenderObject/RenderObject.hpp>
#include <Engine/Renderer/RenderObject/RenderObjectManager.hpp>
#include <Engine/Component/GeometryComponent.hpp>

#include "material.hpp"

void
initQuad(Ra::GuiBase::BaseApplication &app)
{

        //! [Creating the cube]
    auto cube = Ra::Core::Geometry::makeZNormalQuad( {1_ra, 1_ra} );
    //! [Creating the cube]

    //! [Create the engine entity for the cube]
    auto e = app.m_engine->getEntityManager()->createEntity( "Green cube" );
    //! [Create the engine entity for the cube]

    //! [Create a geometry component with the cube]
    auto c = new Ra::Engine::TriangleMeshComponent( "Cube Mesh", e, std::move( cube ), nullptr );
    //! [Create a geometry component with the cube]

    //! [Register the entity/component association to the geometry system ]
    auto geometrySystem = app.m_engine->getSystem( "GeometrySystem" );
    geometrySystem->addComponent( e, c );
    //! [Register the entity/component association to the geometry system ]

    // 3. Setup a Ra::Engine::ShaderConfiguration that uses these shaders
    Ra::Engine::ShaderConfiguration myConfig{"MyColorComputation"};
    myConfig.addShaderSource( Ra::Engine::ShaderType::ShaderType_VERTEX, vertexShaderSource );
    myConfig.addShaderSource( Ra::Engine::ShaderType::ShaderType_FRAGMENT, fragmentShaderSource );
    Ra::Engine::ShaderConfigurationFactory::addConfiguration( myConfig );
    // 4. Build a render technique that use this configuration
    auto renderTechnique = Ra::Core::make_shared<Ra::Engine::RenderTechnique>();
    renderTechnique->setConfiguration( myConfig, Ra::Engine::DefaultRenderingPasses::LIGHTING_OPAQUE );
    // 5. Create and associate the parameter provider with the RenderTechnique
    auto parameterProvider = std::make_shared<MyParameterProvider>();
    parameterProvider->setOrComputeTheParameterValues();
    renderTechnique->setParametersProvider(parameterProvider);
    // 6. Associate the render technique with a geometry in a Ra::Engine::RenderObject

    auto ro    = Ra::Engine::RadiumEngine::getInstance()->getRenderObjectManager()->getRenderObject(
        c->m_renderObjects[0]);
    ro->setRenderTechnique( renderTechnique );
}

int main( int argc, char* argv[] ) {
    Ra::GuiBase::BaseApplication app( argc, argv, Ra::GuiBase::SimpleWindowFactory {} );

    initQuad( app );

    return app.exec();
}