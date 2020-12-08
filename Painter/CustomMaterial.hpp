#pragma once

#include <Engine/RaEngine.hpp>

#include <Core/Asset/MaterialData.hpp>
#include <Core/Utils/Color.hpp>
#include <Engine/Renderer/Material/Material.hpp>
#include <Engine/Renderer/RenderTechnique/ShaderConfigFactory.hpp>

namespace Ra {
namespace Engine {
// Predeclare the Exteernal/Internal material representation converter
class CustomMaterialConverter;
} // Engine

namespace Core {
namespace Asset {

/**
 * External material representation
 *  --> For now, this allow to use our custom material to create geometry component as only
 *  data from asset could be used in the current Radium implementation to create RenderObjects
 */
class RA_CORE_API CustomMaterialData : public MaterialData
{
    friend class Ra::Engine::CustomMaterialConverter;
  public:
    explicit CustomMaterialData(const std::string& instanceName,
                                Core::Utils::Color color = Ra::Core::Utils::Color::Red(),
                                Scalar scale = .5_ra) :
        MaterialData( instanceName, "CustomMaterial" ),
        m_colorParameter {color}, m_scalarParameter {scale} {}
  private:
    /// The base color of the material
    Core::Utils::Color m_colorParameter { Ra::Core::Utils::Color::Red() };
    // The scale of the color
    Scalar m_scalarParameter {.5_ra};
};

} // Asset
} // Core

namespace Engine {

/**
 * Converter from an external representation (comming from IO or ...) to internal representation.
 * Such a converter is used when initializing the RenderObjects from external representation of materials
 */
class RA_ENGINE_API CustomMaterialConverter final
{
  public:
    CustomMaterialConverter()  = default;
    ~CustomMaterialConverter() = default;
    Material* operator()( const Ra::Core::Asset::MaterialData* toconvert );
};

/**
 * Shader source code. (This is yours)
 */
// Vertex shader source code
const std::string _vertexShaderSource{
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
const std::string _fragmentShaderSource{
    "layout (location = 0) in  vec3 in_pos;\n"
    "layout (location = 0) out vec4 out_color;\n"
    "uniform vec4 aColorUniform;\n"
    "uniform float aScalarUniform;\n"
    "void main(void)\n"
    "{\n"
    "    out_color =  vec4(in_pos,1.)*aScalarUniform;\n"
    "}\n"};

/**
 * Definition of the Custom Material to compatible with the Radium Management of RenderObjects/GeometryComponents
 */
class RA_ENGINE_API CustomMaterial : public Material
{
  public:

    /**
     * Construct a named material
     * @param name The name of the material
     * @param color The initial color
     * @param scale The initial scale
     */
    explicit CustomMaterial( const std::string& instanceName,
                             Core::Utils::Color color,
                             Scalar scale ) :
                                Material( instanceName, "CustomMaterial",
                                          Material::MaterialAspect::MAT_OPAQUE ),
                             m_colorParameter {color}, m_scalarParameter {scale} {}

    /**
     * Destructor.
     */
    ~CustomMaterial() override = default;

    /**
     * Update the openGL state of the material.
     * This state also consist in updating the parameter provider of the Material
     */
    void updateGL() override final {
        // Method called before drawing each frame in Renderer::updateRenderObjectsInternal.
        // The name of the parameter corresponds to the shader's uniform name.
        m_renderParameters.addParameter( "aColorUniform", m_colorParameter );
        m_renderParameters.addParameter( "aScalarUniform", m_scalarParameter );
    }

    /** Set or compute the material parameter
     *  This method could be called outside of the rendering loop to alter the material properties
     *  To do that, after the Component RenderObject is created, just get the associated material from the RenderObjects
     */
    void setOrComputeTheParameterValues() {
        // client side computation of the parameters, e.g.
        m_colorParameter = Ra::Core::Utils::Color::Red();
        m_scalarParameter = .5_ra;
    }

    /**
     * Register the material in the material library.
     * After registration, the material could be instantiated by any Radium system, renderer,
     * plugin, ...
     */
    static void registerMaterial() {
        // Defining the material converter
        EngineMaterialConverters::registerMaterialConverter( "CustomMaterial",
                                                             CustomMaterialConverter() );
        Ra::Engine::ShaderConfiguration myConfig{ "CustomMaterial" };
        myConfig.addShaderSource( Ra::Engine::ShaderType::ShaderType_VERTEX, _vertexShaderSource );
        myConfig.addShaderSource( Ra::Engine::ShaderType::ShaderType_FRAGMENT, _fragmentShaderSource );
        Ra::Engine::ShaderConfigurationFactory::addConfiguration( myConfig );

        // Might be helpful to add also Z-prepass configuration for the Forward Renderer ...

        // Register the technique builder for the custom material
        // The technique builder will be called each time a new render object is added to the Radium ecosystem
        Ra::Engine::EngineRenderTechniques::registerDefaultTechnique(
            "CustomMaterial",

            []( Ra::Engine::RenderTechnique& rt, bool isTransparent ) {
              // Configure the technique to render this object using forward Renderer or any
              // compatible one Main pass (Mandatory) : BlinnPhong
              auto lightpass =
                  Ra::Engine::ShaderConfigurationFactory::getConfiguration( "CustomMaterial" );
              rt.setConfiguration( *lightpass, DefaultRenderingPasses::LIGHTING_OPAQUE );

              // Z prepass (Recommended) :

            } );
    }

    /**
     * Remove the material from the material library.
     * After removal, the material is no more available, ...
     */
    static void unregisterMaterial() {
        EngineMaterialConverters::removeMaterialConverter( "CustomMaterial" );
        EngineRenderTechniques::removeDefaultTechnique( "CustomMaterial" );
    }

  public:
    /// The base color of the material
    Core::Utils::Color m_colorParameter { Ra::Core::Utils::Color::Red() };
    // The scale of the color
    Scalar m_scalarParameter {.5_ra};
};

inline Material* CustomMaterialConverter::operator()( const Ra::Core::Asset::MaterialData* toconvert ) {
    auto mat = static_cast<const Core::Asset::CustomMaterialData *>(toconvert);
    return new CustomMaterial( mat->getName(),
                               mat->m_colorParameter,
                               mat->m_scalarParameter);
}

} // namespace Engine
} // namespace Ra

