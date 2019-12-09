#include "DummyComponent.hpp"

#include <Engine/Renderer/Mesh/Mesh.hpp>

namespace DummyPlugin {
DummyComponent::DummyComponent( const std::string& name, Ra::Engine::Entity* entity  )
  : Ra::Engine::Component( name, entity ) {}

DummyComponent::~DummyComponent() {}

void DummyComponent::initialize() {}

} // namespace DummyPlugin
