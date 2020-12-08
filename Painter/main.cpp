// Include Radium base application and its simple Gui
#include <GuiBase/BaseApplication.hpp>
#include <GuiBase/RadiumWindow/SimpleWindowFactory.hpp>

// include the Engine/entity/component interface
#include <Core/Geometry/MeshPrimitives.hpp>
#include <Engine/Component/GeometryComponent.hpp>
#include <Engine/Managers/EntityManager/EntityManager.hpp>
#include <Engine/System/GeometrySystem.hpp>

// include the custom material definiton
#include "CustomMaterial.hpp"

void initQuad(Ra::GuiBase::BaseApplication &app)
{
    //! [Creating the quad]
    auto quad = Ra::Core::Geometry::makeZNormalQuad( {1_ra, 1_ra} );

    //! [Create the engine entity for the quad]
    auto e = app.m_engine->getEntityManager()->createEntity( "Quad Entity" );

    //! [Create Parameter provider (here the custom material) for the shader]
    Ra::Core::Asset::CustomMaterialData mat {"Quad Material"};

    //! [Create a geometry component using the custom material]
    auto c = new Ra::Engine::TriangleMeshComponent( "Quad Mesh", e, std::move( quad ), &mat );

    //! [Register the entity/component association to the geometry system ]
    auto system = app.m_engine->getSystem( "GeometrySystem" );
    system->addComponent( e, c );

    // Initialize all OpenGL state for the scene content
    app.m_mainWindow->postLoadFile( "Cube" );
}

int main( int argc, char* argv[] ) {
    Ra::GuiBase::BaseApplication app( argc, argv, Ra::GuiBase::SimpleWindowFactory {} );

    //! [add the custom material to the material system]
    Ra::Engine::CustomMaterial::registerMaterial();

    //! [Populate the Radium ecosystem]
    initQuad( app );

    return app.exec();
}
