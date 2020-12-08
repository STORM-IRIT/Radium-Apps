// Include Radium base application and its simple Gui
#include <GuiBase/BaseApplication.hpp>
#include <GuiBase/RadiumWindow/SimpleWindowFactory.hpp>

// include the Engine/entity/component interface
#include <Core/Geometry/MeshPrimitives.hpp>
#include <Engine/Component/GeometryComponent.hpp>
#include <Engine/Managers/EntityManager/EntityManager.hpp>
#include <Engine/System/GeometrySystem.hpp>

#include <Core/Utils/Color.hpp>

#include "material.hpp"


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
const std::string vertex{
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
const std::string fragment{
    "layout (location = 0) in  vec3 in_pos;\n"
    "layout (location = 0) out vec4 out_color;\n"
     "uniform vec4 aColorUniform;\n"
     "uniform float aScalarUniform;\n"
    "void main(void)\n"
    "{\n"
    "    out_color =  vec4(in_pos,1.)*aScalarUniform;\n"
    "}\n"};


void
initQuad(Ra::GuiBase::BaseApplication &app)
{

    //! [Creating the quad]
    auto cube = Ra::Core::Geometry::makeZNormalQuad( {1_ra, 1_ra} );

    //! [Create the engine entity for the cube]
    auto e = app.m_engine->getEntityManager()->createEntity( "Quad Entity" );

    //! [Create Parameter provider for the shader]
    auto paramProvider = std::make_shared<MyParameterProvider>();
    paramProvider->setOrComputeTheParameterValues();

    //! [Create a geometry component]
    auto c = new Ra::Engine::TriangleMeshComponent( "Quad Mesh", e, std::move( cube ), nullptr );

    //! [Create a CustomShaderComponent]
    auto c2 = new CustomShaderComponent( "Quad Mesh Shader", e, c, paramProvider, vertex, fragment);

    //! [Register the entity/component association to the geometry system ]
    auto system = app.m_engine->getSystem( "GeometrySystem" );
    system->addComponent( e, c );
    system->addComponent( e, c2 );

    // Initialize is not call automatically, why ? 
    // What is the purpose of this function if it is not used ?
    c2->initialize();

    // Calling this function remove the custom material, I am not sure to understand why
    //app.m_mainWindow->postLoadFile( "Cube" );
}

int main( int argc, char* argv[] ) {
    Ra::GuiBase::BaseApplication app( argc, argv, Ra::GuiBase::SimpleWindowFactory {} );

    initQuad( app );

    return app.exec();
}