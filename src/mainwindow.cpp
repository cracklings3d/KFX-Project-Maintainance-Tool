#include <QFileDialog>
#include <iostream>
#include <qdebug.h>

#include "./ui_mainwindow.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(m_context, SIGNAL(projectFileChanged(QUrl)), this,
          SLOT(onNewProject(QUrl)));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_LocateProjectButton_clicked() {
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

  m_context->setProjectFile(urls[0]);
}

void MainWindow::onNewProject(QUrl new_project) {
  if (new_project.isEmpty()) {
    setPage(MainWindowPage::LocateProject);
    return;
  }

  setWindowTitle(new_project.fileName(QUrl::ComponentFormattingOption::PrettyDecoded));
  ui->ProjectRootPath->setText(new_project.path());
  setPage(MainWindowPage::General);
}

bool MainWindow::validateProjectDir(const QUrl &url) { return true; }

void MainWindow::setPage(MainWindowPage page) {
  ui->PageSelector->setCurrentIndex(static_cast<int>(page));
}

void UnrealProjectContext::setProjectFile(const QUrl &url) {
  m_projectFile = url;
  emit projectFileChanged(url);
}

const QUrl &UnrealProjectContext::projectFile() const { return m_projectFile; }

void UnrealProjectContext::resetProjectFile() {
  setProjectFile({});
  emit projectFileChanged({});
}
