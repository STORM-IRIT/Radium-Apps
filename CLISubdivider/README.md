# Radium Subdivider Command-Line Interface

Load a triangle mesh and subdivide it using OpenMesh. 

## CLI parameters
```cpp
std::cout << "Usage :\n"
          << argv[0] << " -i input.obj -o output -s type -n iteration  \n\n"
          << " .obj extension is added automatically to output filename\n"
          << "input\t\t the name (with .obj extension) of the file to load, if no input is "
            "given, a simple cube is used\n"
          << "type \t\t is a string for the subdivider type name : catmull, loop\n"
          << "iteration \t (default is 1) is a positive integer to specify the number of "
            "iteration of subdivision\n\n";
```


## Code breakdown
Excluding command parsing, only very few steps are required to load, simplify and save the object:

 1. Load triangular mesh or generate 
```cpp
Ra::Core::Geometry::TriangleMesh mesh;
Ra::IO::OBJFileManager obj;

// Load geometry as triangle
if ( inputFilename.empty() ) { mesh = Ra::Core::Geometry::makeBox(); }
else                         { obj.load( inputFilename, mesh ); }
```

 2. Create topological structure from the loaded geometry, and OpenMesh datastructures.
```cpp
// Create topological structure
Ra::Core::Geometry::TopologicalMesh topologicalMesh( mesh );

// Create CatmullClarkSubdivider
using Subdivider = 
OpenMesh::Subdivider::Uniform::SubdividerT<Ra::Core::Geometry::TopologicalMesh, Scalar>; 
Subdiviser subdiviser(Ra::Core::Geometry::CatmullClarkSubdivider);
```

 3. Create OpenMesh subdivider and process geometry
```cpp
subdivider.attach( topologicalMesh );
subdivider( nIter );
subdivider.detach();
```

 4. Convert and save simplified geometry 
```cpp
// Convert processed topological structure to triangle mesh
mesh = topologicalMesh.toTriangleMesh();

// Save triangle mesh to obj file
obj.save( outputFilename, mesh );
```