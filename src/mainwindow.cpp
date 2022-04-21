#include <QFileDialog>
#include <iostream>
#include <qdebug.h>

#include "./ui_mainwindow.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
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
  }

  if (!validateProjectDir(urls[0])){
    statusBar()->showMessage(tr("Error: invalid input."));
  }


}

bool MainWindow::validateProjectDir(const QUrl &url) {
  return true;
}

void UnrealProjectContext::setProjectFile(const QUrl &url) { m_projectFile = url; }

const QUrl &UnrealProjectContext::projectFile() const { return m_projectFile; }

void UnrealProjectContext::resetProjectFile() {
  setProjectFile({}); // TODO: Adapt to use your actual default value
}
