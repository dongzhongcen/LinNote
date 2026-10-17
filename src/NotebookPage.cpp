#include "NotebookPage.h"
#include "PortablePaths.h"
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QSplitter>
#include <QTextStream>
#include <QVBoxLayout>
#include <QUuid>

NotebookPage::NotebookPage(QWidget *parent)
    : QWidget(parent)
{
    m_list = new QListWidget(this);
    m_title = new QLineEdit(this);
    m_title->setPlaceholderText(tr("标题"));
    m_body = new QPlainTextEdit(this);
    m_body->setPlaceholderText(tr("写笔记…（纯文本，保存在便携 data/notes）"));
    m_saveBtn = new QPushButton(tr("保存"), this);
    m_newBtn = new QPushButton(tr("新建"), this);
    m_delBtn = new QPushButton(tr("删除"), this);

    auto *btns = new QHBoxLayout;
    btns->addWidget(m_newBtn);
    btns->addWidget(m_saveBtn);
    btns->addWidget(m_delBtn);
    btns->addStretch();

    auto *right = new QWidget(this);
    auto *rightLay = new QVBoxLayout(right);
    rightLay->setContentsMargins(0, 0, 0, 0);
    rightLay->addLayout(btns);
    rightLay->addWidget(m_title);
    rightLay->addWidget(m_body);

    auto *split = new QSplitter(Qt::Horizontal, this);
    split->addWidget(m_list);
    split->addWidget(right);
    split->setStretchFactor(0, 1);
    split->setStretchFactor(1, 3);

    auto *root = new QVBoxLayout(this);
    root->addWidget(new QLabel(tr("笔记本：每条笔记一个文件；删除会直接移除文件，不留缓存。"), this));
    root->addWidget(split);

    refreshList();

    connect(m_list, &QListWidget::currentRowChanged, this, [this](int) { loadSelected(); });
    connect(m_saveBtn, &QPushButton::clicked, this, &NotebookPage::saveCurrent);
    connect(m_newBtn, &QPushButton::clicked, this, &NotebookPage::newNote);
    connect(m_delBtn, &QPushButton::clicked, this, &NotebookPage::deleteSelected);
}

QString NotebookPage::notePath(const QString &id) const
{
    return PortablePaths::notesDir() + QLatin1Char('/') + id + QStringLiteral(".txt");
}

QString NotebookPage::currentId() const
{
    auto *item = m_list->currentItem();
    return item ? item->data(Qt::UserRole).toString() : QString();
}

void NotebookPage::refreshList()
{
    const auto keep = currentId();
    m_list->clear();
    QDir dir(PortablePaths::notesDir());
    const auto files = dir.entryList({QStringLiteral("*.txt")}, QDir::Files, QDir::Time);
    for (const auto &name : files) {
        const auto id = QFileInfo(name).completeBaseName();
        QString title = id;
        QFile f(dir.filePath(name));
        if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&f);
            const auto first = in.readLine();
            if (first.startsWith(QStringLiteral("# ")))
                title = first.mid(2).trimmed();
            else if (!first.isEmpty())
                title = first.trimmed();
        }
        auto *item = new QListWidgetItem(title);
        item->setData(Qt::UserRole, id);
        m_list->addItem(item);
    }
    for (int i = 0; i < m_list->count(); ++i) {
        if (m_list->item(i)->data(Qt::UserRole).toString() == keep) {
            m_list->setCurrentRow(i);
            return;
        }
    }
    if (m_list->count() > 0)
        m_list->setCurrentRow(0);
    else {
        m_loadedId.clear();
        m_title->clear();
        m_body->clear();
    }
}

void NotebookPage::loadSelected()
{
    const auto id = currentId();
    if (id.isEmpty())
        return;
    QFile f(notePath(id));
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&f);
    const auto first = in.readLine();
    QString title;
    QString body;
    if (first.startsWith(QStringLiteral("# "))) {
        title = first.mid(2).trimmed();
        body = in.readAll();
    } else {
        title = id;
        body = first + QLatin1Char('\n') + in.readAll();
    }
    m_loadedId = id;
    m_title->setText(title);
    m_body->setPlainText(body);
}

void NotebookPage::saveCurrent()
{
    QString id = m_loadedId;
    if (id.isEmpty())
        id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    QFile f(notePath(id));
    if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        QMessageBox::warning(this, tr("保存失败"), f.errorString());
        return;
    }
    QTextStream out(&f);
    out << "# " << m_title->text().trimmed() << "\n";
    out << m_body->toPlainText();
    m_loadedId = id;
    refreshList();
}

void NotebookPage::newNote()
{
    m_loadedId.clear();
    m_list->clearSelection();
    m_title->setText(tr("新笔记"));
    m_body->clear();
    m_title->setFocus();
}

void NotebookPage::deleteSelected()
{
    const auto id = currentId();
    if (id.isEmpty())
        return;
    const auto path = notePath(id);
    if (QMessageBox::question(this, tr("确认删除"),
                              tr("将永久删除笔记文件（无残留）：\n%1").arg(path))
        != QMessageBox::Yes)
        return;
    if (QFile::exists(path) && !QFile::remove(path)) {
        QMessageBox::warning(this, tr("删除失败"), tr("无法删除：%1").arg(path));
        return;
    }
    m_loadedId.clear();
    m_title->clear();
    m_body->clear();
    refreshList();
}
