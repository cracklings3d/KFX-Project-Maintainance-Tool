#ifndef KPM_MAINWINDOW_H
#define KPM_MAINWINDOW_H

#include <memory>

#include <QLayout>
#include <QMainWindow>
#include <QQuickView>
#include <QWidget>

#include "UnrealProjectContext.h"

namespace KPM {
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

enum class MainWindowPage {
  LocateProject = 0,
  General = 1,
};

class ProgramContext : public QObject {
  Q_OBJECT

public:
  ProgramContext(QMainWindow *parent) { setParent(parent); }

  QStatusBar *statusBar();

private:
};

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  ProgramContext *getContext();

signals:
  void userLocatedProject(const QUrl &url);

public slots:
  void on_LocateProjectButton_clicked();
  void onNewProject(QUrl new_project);
  void onOpenUserConfDialog();

private:
  Ui::MainWindow *ui;

  UnrealProjectContext *m_unrealProjectContext = new UnrealProjectContext(this);
  ProgramContext *m_programContext = new ProgramContext(this);

  bool validateProjectDir(const QUrl &url);
  void setPage(MainWindowPage page);
};
} // namespace KPM
#endif // KPM_MAINWINDOW_H
