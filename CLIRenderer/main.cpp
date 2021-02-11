// Include Radium base application and its simple Gui
#include <Gui/BaseApplication.hpp>
#include <Gui/RadiumWindow/SimpleWindowFactory.hpp>

// include the Viewer to demonstrate dynamic edition of materials
#include <Gui/Viewer/Viewer.hpp>
#include <Core/Types.hpp>

#include <string>

#include <QObject>

int main( int argc, char* argv[] ) {
    Ra::Gui::BaseApplication app( argc, argv, "CLIRenderer" );
    app.initialize( Ra::Gui::SimpleWindowFactory {} );

    // Load file when application is ready
    QAbstractAnimation::connect( &app, &QGuiApplication::applicationStateChanged,
    [&app, &argv] (Qt::ApplicationState state) {
        app.loadFile(argv[1]);
    });

    // Render and save to disk when file has been loaded
    QAbstractAnimation::connect( &app, &Ra::Gui::BaseApplication::loadComplete,
    [&app, &argv] () {
        std::cout << " plot " << std::endl; 
        // update display
        app.radiumFrame();
        // save display to file
        app.recordFrame();
        // request exiting application
        app.appNeedsToQuit();
    });

    return app.exec();
}
