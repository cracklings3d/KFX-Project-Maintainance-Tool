#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLayout>
#include <QMainWindow>
#include <QQuickView>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class UnrealProjectContext {
  Q_OBJECT

public:
  void setProjectFile(const QUrl &url);
  const QUrl &projectFile() const;
  void resetProjectFile();

private:
  QUrl m_projectFile;
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

private:
  Ui::MainWindow *ui;

  bool validateProjectDir(const QUrl &url);
};
#endif // MAINWINDOW_H
