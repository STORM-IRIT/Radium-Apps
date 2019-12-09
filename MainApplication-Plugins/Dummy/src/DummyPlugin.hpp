#ifndef DUMMYPLUGIN_DUMMYPLUGIN_HPP
#define DUMMYPLUGIN_DUMMYPLUGIN_HPP

#include <DummyPluginMacros.hpp>

#include <QObject>
#include <QtPlugin>

#include <PluginBase/RadiumPluginInterface.hpp>

class QLabel;

namespace Ra {
namespace Engine {
class RadiumEngine;
}
} // namespace Ra

namespace DummyPlugin {
class DummySystem;

class DUMMY_PLUGIN_API DummyPlugin : public QObject, Ra::Plugins::RadiumPluginInterface
{
    Q_OBJECT
    Q_RADIUM_PLUGIN_METADATA
    Q_INTERFACES( Ra::Plugins::RadiumPluginInterface )

  public:
    DummyPlugin() = default;
    ~DummyPlugin() override;

    void registerPlugin( const Ra::Plugins::Context& context ) override;

    bool doAddWidget( QString& name ) override;
    QWidget* getWidget() override;

    bool doAddMenu() override;
    QMenu* getMenu() override;

    inline bool doAddAction( int& ) override { return false; }
    inline QAction* getAction( int ) override { return nullptr; }

  private slots:
    void sayHello();

  private:
    DummySystem* m_system{nullptr};
    QLabel* m_label{nullptr};
};

} // namespace DummyPlugin

#endif // FANCYMESHPLUGIN_HPP_
