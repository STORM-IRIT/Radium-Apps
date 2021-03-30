#include <Core/Geometry/CatmullClarkSubdivider.hpp>
#include <Core/Geometry/LoopSubdivider.hpp>
#include <Core/Geometry/MeshPrimitives.hpp>
#include <Core/Geometry/deprecated/TopologicalMesh.hpp>
#include <Core/Utils/Log.hpp>
#include <IO/deprecated/OBJFileManager.hpp>
#include <memory>

/// Macro used for testing only, to add attibutes to the TopologicalMesh
/// before subdivisition
/// \FIXME Must be removed once using Radium::IO with attribute loading.
//#define TEST_ATTRIBUTES_SUBDIV

struct args {
    bool valid;
    int iteration;
    std::string outputFilename;
    std::string inputFilename;
    std::unique_ptr<
        OpenMesh::Subdivider::Uniform::SubdividerT<Ra::Core::Geometry::deprecated::TopologicalMesh, Scalar>>
        subdivider;
};

void printHelp( char* argv[] ) {
    std::cout << "Usage :\n"
              << argv[0] << " -i input.obj -o output -s type -n iteration  \n\n"
              << " .obj extension is added automatically to output filename\n"
              << "input\t\t the name (with .obj extension) of the file to load, if no input is "
                 "given, a simple cube is used\n"
              << "type \t\t is a string for the subdivider type name : catmull, loop\n"
              << "iteration \t (default is 1) is a positive integer to specify the number of "
                 "iteration of subdivision\n\n";
    /// \FIXME Use Radium::IO to load and save meshes.
    std::cout
        << "Warning: The Subdivide application does not use Radium::IO for loading/saving "
        << "files. Input *.obj files must list only vertex position (v) and vertex normal (vn), "
        << "and the face list.\n"
        << "Other features of the OBJ file format are not supported and might lead to "
        << "unexpected behaviors." << std::endl;
}

args processArgs( int argc, char* argv[] ) {
    args ret;
    bool outputFilenameSet{false};
    bool subdividerSet{false};
    ret.iteration = 1;

    for ( int i = 1; i < argc; i += 2 )
    {
        if ( std::string( argv[i] ) == std::string( "-i" ) )
        {
            if ( i + 1 < argc ) { ret.inputFilename = argv[i + 1]; }
        }
        else if ( std::string( argv[i] ) == std::string( "-o" ) )
        {
            if ( i + 1 < argc )
            {
                ret.outputFilename = argv[i + 1];
                outputFilenameSet  = true;
            }
        }
        else if ( std::string( argv[i] ) == std::string( "-s" ) )
        {
            if ( i + 1 < argc )
            {
                std::string a{argv[i + 1]};
                subdividerSet = true;
                if ( a == std::string( "catmull" ) )
                {
                    ret.subdivider = std::make_unique<Ra::Core::Geometry::CatmullClarkSubdivider>();
                }
                else if ( a == std::string( "loop" ) )
                { ret.subdivider = std::make_unique<Ra::Core::Geometry::LoopSubdivider>(); }
                else
                { subdividerSet = false; }
            }
        }
        else if ( std::string( argv[i] ) == std::string( "-n" ) )
        {
            if ( i + 1 < argc ) { ret.iteration = std::stoi( std::string( argv[i + 1] ) ); }
        }
    }
    ret.valid = outputFilenameSet && subdividerSet;
    return ret;
}

int main( int argc, char* argv[] ) {
    using namespace Ra::Core::Utils; // log
    args a = processArgs( argc, argv );
    if ( !a.valid ) { printHelp( argv ); }
    else
    {
        Ra::Core::Geometry::TriangleMesh mesh;
        Ra::IO::OBJFileManager obj;

        // Load geometry as triangle
        if ( a.inputFilename.empty() ) { mesh = Ra::Core::Geometry::makeBox(); }
        else                           { obj.load( a.inputFilename, mesh ); }

        // Create topological structure
        Ra::Core::Geometry::deprecated::TopologicalMesh topologicalMesh( mesh );

        // Create OpenMesh subdivider, and process topological structure
        a.subdivider->attach( topologicalMesh );
        ( *a.subdivider )( a.iteration );
        a.subdivider->detach();

        // Convert processed topological structure to triangle mesh
        mesh = topologicalMesh.toTriangleMesh();

        // Save triangle mesh to obj file
        obj.save( a.outputFilename, mesh );
    }
    return 0;
}
