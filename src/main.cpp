#include "MainWindow.h"
#include "PortablePaths.h"
#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName(QStringLiteral("LinNote"));
    QApplication::setOrganizationName(QStringLiteral("dongzhongcen"));
    QApplication::setApplicationVersion(QStringLiteral("0.1.0"));

    // Portable: never use roaming AppData / XDG config for notes or downloads.
    PortablePaths::dataDir();
    PortablePaths::notesDir();
    PortablePaths::downloadsDir();

    MainWindow w;
    w.show();
    return app.exec();
}
