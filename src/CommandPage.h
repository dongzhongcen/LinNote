#pragma once
#include <QWidget>
#include <QVector>
#include <QJsonObject>

class QLineEdit;
class QListWidget;
class QTextEdit;

struct CommandEntry {
    QString id;
    QString name;
    QString summary;
    QString usage;
    QString example;
    QStringList tags;
};

class CommandPage : public QWidget {
    Q_OBJECT
public:
    explicit CommandPage(QWidget *parent = nullptr);

private:
    void loadCatalog();
    void refreshList(const QString &filter);
    void showEntry(const CommandEntry &e);

    QVector<CommandEntry> m_entries;
    QLineEdit *m_search = nullptr;
    QListWidget *m_list = nullptr;
    QTextEdit *m_detail = nullptr;
};
