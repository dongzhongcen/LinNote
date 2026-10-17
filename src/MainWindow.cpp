#include "MainWindow.h"
#include "CommandPage.h"
#include "ConfigPage.h"
#include "NotebookPage.h"
#include "PortablePaths.h"
#include <QLabel>
#include <QStatusBar>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("LinNote — 便携笔记本"));
    resize(960, 640);

    auto *tabs = new QTabWidget(this);
    tabs->addTab(new NotebookPage(tabs), tr("笔记本"));
    tabs->addTab(new CommandPage(tabs), tr("指令查询"));
    tabs->addTab(new ConfigPage(tabs), tr("配置下载"));
    setCentralWidget(tabs);

    statusBar()->showMessage(
        tr("便携模式 · 数据目录：%1").arg(PortablePaths::dataDir()));
}
