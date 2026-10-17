#pragma once
#include <QString>

/** All user data lives next to the executable (portable). */
class PortablePaths {
public:
    static QString appDir();
    static QString dataDir();
    static QString notesDir();
    static QString downloadsDir();
    static QString ensureDir(const QString &path);
};
