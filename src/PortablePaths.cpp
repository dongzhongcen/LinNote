#include "PortablePaths.h"
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>

QString PortablePaths::appDir()
{
    return QCoreApplication::applicationDirPath();
}

QString PortablePaths::ensureDir(const QString &path)
{
    QDir().mkpath(path);
    return path;
}

QString PortablePaths::dataDir()
{
    return ensureDir(appDir() + QStringLiteral("/data"));
}

QString PortablePaths::notesDir()
{
    return ensureDir(dataDir() + QStringLiteral("/notes"));
}

QString PortablePaths::downloadsDir()
{
    return ensureDir(dataDir() + QStringLiteral("/downloads"));
}
