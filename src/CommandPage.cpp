#include "CommandPage.h"
#include <QFile>
#include <QHBoxLayout>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QSplitter>
#include <QTextEdit>
#include <QVBoxLayout>

CommandPage::CommandPage(QWidget *parent)
    : QWidget(parent)
{
    m_search = new QLineEdit(this);
    m_search->setPlaceholderText(tr("搜索命令名、简介或标签…"));
    m_list = new QListWidget(this);
    m_detail = new QTextEdit(this);
    m_detail->setReadOnly(true);

    auto *left = new QWidget(this);
    auto *leftLay = new QVBoxLayout(left);
    leftLay->setContentsMargins(0, 0, 0, 0);
    leftLay->addWidget(m_search);
    leftLay->addWidget(m_list);

    auto *split = new QSplitter(Qt::Horizontal, this);
    split->addWidget(left);
    split->addWidget(m_detail);
    split->setStretchFactor(0, 1);
    split->setStretchFactor(1, 2);

    auto *root = new QVBoxLayout(this);
    root->addWidget(new QLabel(tr("内置常见 Linux 命令速查（可离线）"), this));
    root->addWidget(split);

    loadCatalog();
    refreshList(QString());

    connect(m_search, &QLineEdit::textChanged, this, &CommandPage::refreshList);
    connect(m_list, &QListWidget::currentRowChanged, this, [this](int row) {
        if (row < 0 || row >= m_list->count())
            return;
        const auto id = m_list->item(row)->data(Qt::UserRole).toString();
        for (const auto &e : m_entries) {
            if (e.id == id) {
                showEntry(e);
                break;
            }
        }
    });
}

void CommandPage::loadCatalog()
{
    m_entries.clear();
    QFile f(QStringLiteral(":/commands/catalog.json"));
    if (!f.open(QIODevice::ReadOnly))
        return;
    const auto doc = QJsonDocument::fromJson(f.readAll());
    for (const auto &v : doc.array()) {
        const auto o = v.toObject();
        CommandEntry e;
        e.id = o.value(QStringLiteral("id")).toString();
        e.name = o.value(QStringLiteral("name")).toString();
        e.summary = o.value(QStringLiteral("summary")).toString();
        e.usage = o.value(QStringLiteral("usage")).toString();
        e.example = o.value(QStringLiteral("example")).toString();
        for (const auto &t : o.value(QStringLiteral("tags")).toArray())
            e.tags << t.toString();
        m_entries.push_back(e);
    }
}

void CommandPage::refreshList(const QString &filter)
{
    m_list->clear();
    const auto q = filter.trimmed().toLower();
    for (const auto &e : m_entries) {
        const bool ok = q.isEmpty()
            || e.name.toLower().contains(q)
            || e.summary.toLower().contains(q)
            || e.tags.join(QLatin1Char(' ')).toLower().contains(q);
        if (!ok)
            continue;
        auto *item = new QListWidgetItem(QStringLiteral("%1 — %2").arg(e.name, e.summary));
        item->setData(Qt::UserRole, e.id);
        m_list->addItem(item);
    }
    if (m_list->count() > 0)
        m_list->setCurrentRow(0);
}

void CommandPage::showEntry(const CommandEntry &e)
{
    m_detail->setMarkdown(
        QStringLiteral("## `%1`\n\n%2\n\n### 用法\n\n```\n%3\n```\n\n### 示例\n\n```\n%4\n```\n\n标签：%5")
            .arg(e.name, e.summary, e.usage, e.example, e.tags.join(QStringLiteral(", "))));
}
