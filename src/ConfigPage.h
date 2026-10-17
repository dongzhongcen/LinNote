#pragma once
#include <QWidget>
#include <QVector>

class QListWidget;
class QLabel;
class QNetworkAccessManager;
class QPushButton;

struct ConfigEntry {
    QString id;
    QString name;
    QString summary;
    QString url;
    QString filename;
};

class ConfigPage : public QWidget {
    Q_OBJECT
public:
    explicit ConfigPage(QWidget *parent = nullptr);

private:
    void loadCatalog();
    void refreshList();
    void downloadSelected();
    void deleteSelected(); /** Removes download file completely — no leftover. */
    QString localPathFor(const ConfigEntry &e) const;
    bool isDownloaded(const ConfigEntry &e) const;

    QVector<ConfigEntry> m_entries;
    QListWidget *m_list = nullptr;
    QLabel *m_info = nullptr;
    QPushButton *m_dlBtn = nullptr;
    QPushButton *m_delBtn = nullptr;
    QNetworkAccessManager *m_nam = nullptr;
};
