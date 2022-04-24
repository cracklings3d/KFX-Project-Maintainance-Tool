#ifndef KPM_MAINWINDOW_H
#define KPM_MAINWINDOW_H

#include <memory>

#include <QLayout>
#include <QMainWindow>
#include <QQuickView>
#include <QWidget>

namespace KPM {
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class UnrealProjectContext : public QObject {
  Q_OBJECT

public:
  UnrealProjectContext(QObject *parent = nullptr) : QObject(parent) {}

  void setProjectFile(const QUrl &url);
  const QUrl &projectFile() const;
  void resetProjectFile();

private:
  QUrl m_projectFile;

signals:
  void projectFileChanged(QUrl);
};

enum class MainWindowPage {
  LocateProject = 0,
  General = 1,
};

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

signals:
  void userLocatedProject(const QUrl &url);

public slots:
  void on_LocateProjectButton_clicked();
  void onNewProject(QUrl new_project);
  void onOpenUserConfDialog();

private:
  Ui::MainWindow *ui;

  UnrealProjectContext *m_context = new UnrealProjectContext(this);

  bool validateProjectDir(const QUrl &url);
  void setPage(MainWindowPage page);
};
} // namespace KPM
#endif // KPM_MAINWINDOW_H
