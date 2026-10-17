#include "ConfigPage.h"
#include "PortablePaths.h"
#include <QFile>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QPushButton>
#include <QVBoxLayout>

ConfigPage::ConfigPage(QWidget *parent)
    : QWidget(parent)
    , m_nam(new QNetworkAccessManager(this))
{
    m_list = new QListWidget(this);
    m_info = new QLabel(this);
    m_info->setWordWrap(true);
    m_dlBtn = new QPushButton(tr("下载到便携目录"), this);
    m_delBtn = new QPushButton(tr("删除本地副本"), this);
    m_delBtn->setEnabled(false);

    auto *btns = new QHBoxLayout;
    btns->addWidget(m_dlBtn);
    btns->addWidget(m_delBtn);
    btns->addStretch();

    auto *root = new QVBoxLayout(this);
    root->addWidget(new QLabel(tr("精选常用配置模板；下载保存在程序旁 data/downloads，删除会整文件清除。"), this));
    root->addWidget(m_list);
    root->addWidget(m_info);
    root->addLayout(btns);

    loadCatalog();
    refreshList();

    connect(m_list, &QListWidget::currentRowChanged, this, [this](int row) {
        if (row < 0 || row >= m_entries.size()) {
            m_info->clear();
            m_delBtn->setEnabled(false);
            return;
        }
        const auto &e = m_entries.at(row);
        const bool has = isDownloaded(e);
        m_info->setText(tr("%1\n来源：%2\n本地：%3")
                            .arg(e.summary, e.url,
                                 has ? localPathFor(e) : tr("（尚未下载）")));
        m_delBtn->setEnabled(has);
    });
    connect(m_dlBtn, &QPushButton::clicked, this, &ConfigPage::downloadSelected);
    connect(m_delBtn, &QPushButton::clicked, this, &ConfigPage::deleteSelected);
}

void ConfigPage::loadCatalog()
{
    m_entries.clear();
    QFile f(QStringLiteral(":/configs/catalog.json"));
    if (!f.open(QIODevice::ReadOnly))
        return;
    for (const auto &v : QJsonDocument::fromJson(f.readAll()).array()) {
        const auto o = v.toObject();
        ConfigEntry e;
        e.id = o.value(QStringLiteral("id")).toString();
        e.name = o.value(QStringLiteral("name")).toString();
        e.summary = o.value(QStringLiteral("summary")).toString();
        e.url = o.value(QStringLiteral("url")).toString();
        e.filename = o.value(QStringLiteral("filename")).toString();
        m_entries.push_back(e);
    }
}

QString ConfigPage::localPathFor(const ConfigEntry &e) const
{
    return PortablePaths::downloadsDir() + QLatin1Char('/') + e.filename;
}

bool ConfigPage::isDownloaded(const ConfigEntry &e) const
{
    return QFileInfo::exists(localPathFor(e));
}

void ConfigPage::refreshList()
{
    const int row = m_list->currentRow();
    m_list->clear();
    for (const auto &e : m_entries) {
        const auto mark = isDownloaded(e) ? QStringLiteral("✓ ") : QStringLiteral("· ");
        m_list->addItem(mark + e.name);
    }
    if (row >= 0 && row < m_list->count())
        m_list->setCurrentRow(row);
    else if (m_list->count() > 0)
        m_list->setCurrentRow(0);
}

void ConfigPage::downloadSelected()
{
    const int row = m_list->currentRow();
    if (row < 0 || row >= m_entries.size())
        return;
    const auto e = m_entries.at(row);
    auto *reply = m_nam->get(QNetworkRequest(QUrl(e.url)));
    connect(reply, &QNetworkReply::finished, this, [this, reply, e]() {
        reply->deleteLater();
        if (reply->error() != QNetworkReply::NoError) {
            QMessageBox::warning(this, tr("下载失败"), reply->errorString());
            return;
        }
        QFile out(localPathFor(e));
        if (!out.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            QMessageBox::warning(this, tr("写入失败"), out.errorString());
            return;
        }
        out.write(reply->readAll());
        out.close();
        refreshList();
        QMessageBox::information(this, tr("完成"), tr("已保存到：\n%1").arg(localPathFor(e)));
    });
}

void ConfigPage::deleteSelected()
{
    const int row = m_list->currentRow();
    if (row < 0 || row >= m_entries.size())
        return;
    const auto e = m_entries.at(row);
    const auto path = localPathFor(e);
    if (!QFileInfo::exists(path))
        return;
    if (QMessageBox::question(this, tr("确认删除"),
                              tr("将永久删除本地文件（无回收站残留）：\n%1").arg(path))
        != QMessageBox::Yes)
        return;
    if (!QFile::remove(path)) {
        QMessageBox::warning(this, tr("删除失败"), tr("无法删除：%1").arg(path));
        return;
    }
    // Extra safety: remove empty leftover if any sidecar appeared
    QFileInfo fi(path);
    refreshList();
}
