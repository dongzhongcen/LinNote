#pragma once
#include <QWidget>

class QListWidget;
class QPlainTextEdit;
class QLineEdit;
class QPushButton;

class NotebookPage : public QWidget {
    Q_OBJECT
public:
    explicit NotebookPage(QWidget *parent = nullptr);

private:
    void refreshList();
    void loadSelected();
    void saveCurrent();
    void newNote();
    void deleteSelected(); /** Deletes note file completely under data/notes. */
    QString notePath(const QString &id) const;
    QString currentId() const;

    QListWidget *m_list = nullptr;
    QLineEdit *m_title = nullptr;
    QPlainTextEdit *m_body = nullptr;
    QPushButton *m_saveBtn = nullptr;
    QPushButton *m_newBtn = nullptr;
    QPushButton *m_delBtn = nullptr;
    QString m_loadedId;
};
