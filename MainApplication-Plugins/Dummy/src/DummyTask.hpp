#ifndef DUMMYPLUGIN_DUMMYTASK_HPP
#define DUMMYPLUGIN_DUMMYTASK_HPP

#include <Core/Tasks/Task.hpp>
#include <DummyPluginMacros.hpp>

namespace DummyPlugin {
struct DummyData;

struct DummyParams {
    DummyData* data;
};

class DUMMY_PLUGIN_API DummyTask : public Ra::Core::Task
{
  public:
    DummyTask() = default;
    std::string getName() const override;
    void init( const DummyParams* params );
    void process() override;

  private:
    DummyData* m_data{nullptr};
};

class DummyOtherTask : public Ra::Core::Task
{
  public:
    DummyOtherTask() = default;
    virtual std::string getName() const override;
    void init( const DummyParams* params );
    void process() override;

  private:
    DummyData* m_data{nullptr};
};
} // namespace DummyPlugin

#endif
