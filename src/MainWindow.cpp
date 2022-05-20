#include <QFileDialog>
#include <iostream>
#include <qdebug.h>

#include "./ui_MainWindow.h"
#include "MainWindow.h"
#include "UserConfView.h"
#include "src/UnrealProjectContext.h"

KPM::MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(m_unrealProjectContext, SIGNAL(projectFileChanged(QUrl)), this,
          SLOT(onNewProject(QUrl)));
  connect(m_unrealProjectContext, SIGNAL(log(QString)), this,
          SLOT(onLog(QString)));

  ui->PageSelector->setCurrentIndex(0);
}

KPM::MainWindow::~MainWindow() { delete ui; }

KPM::ProgramContext *KPM::MainWindow::getContext() {
  return m_programContext;
}

void KPM::MainWindow::onLog(QString log) {
  statusBar()->showMessage(log);
}

void KPM::MainWindow::on_LocateProjectButton_clicked() {
  QFileDialog ofd(this);
  ofd.setFileMode(QFileDialog::AnyFile);
  ofd.setViewMode(QFileDialog::Detail);
  ofd.setNameFilter(tr("Unreal Project Files (*.uproject)"));

  //    qDebug() << dir;

  if (!ofd.exec()) {
    statusBar()->showMessage(tr("User cancelled input."));
    return;
  }

  auto urls = ofd.selectedUrls();
  if (urls.isEmpty()) {
    statusBar()->showMessage(tr("Error: no input."));
    return;
  }

  if (!validateProjectDir(urls[0])) {
    statusBar()->showMessage(tr("Error: invalid input."));
    return;
  }

  m_unrealProjectContext->setProjectFile(urls[0]);
}

void KPM::MainWindow::onNewProject(QUrl new_project) {
  if (new_project.isEmpty()) {
    setPage(MainWindowPage::LocateProject);
    return;
  }

  setWindowTitle(new_project.fileName(QUrl::ComponentFormattingOption::PrettyDecoded));
  setPage(MainWindowPage::General);

  updateGeneralTab();
}

void KPM::MainWindow::onOpenUserConfDialog() {
  statusBar()->showMessage(tr("DEBUG MESSAGE"), 2000);
  UserConfView userConfView(this);
  userConfView.exec();
}

void KPM::MainWindow::onUpdateUnrealProject(KPM::UnrealProjectContext *context) {
  auto s = context->serializeDescriptor();
  // TODO
  // TODO
  // TODO
}

void KPM::MainWindow::onProjectPluginsTestSlot() {
  m_unrealProjectContext->testFunc();
}

bool KPM::MainWindow::validateProjectDir(const QUrl &url) { return true; }

void KPM::MainWindow::setPage(MainWindowPage page) {
  ui->PageSelector->setCurrentIndex(static_cast<int>(page));
}

void KPM::MainWindow::updateGeneralTab() {
  auto desc = m_unrealProjectContext->getProjectDescriptor();

  ui->categoryEdit->setEditText(desc->category);
  ui->descriptionEdit->setPlainText(desc->description);
  ui->fileVersionText->setNum(desc->fileVersion);
  ui->engineAssiciationEdit->addItem("4.27");
  ui->engineAssiciationEdit->addItem("5.0");
  ui->engineAssiciationEdit->setCurrentText("4.27");
}

QStatusBar *KPM::ProgramContext::statusBar() {
  return static_cast<QMainWindow *>(parent())->statusBar();
}
