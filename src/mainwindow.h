#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QLayout>
#include <QMainWindow>
#include <QQuickView>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class UnrealProjectContext : public QObject {
  Q_OBJECT

public:
  void setProjectFile(const QUrl &url);
  const QUrl &projectFile() const;
  void resetProjectFile();

private:
  QUrl m_projectFile;

signals:
  void projectFileChanged(QUrl);
};

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

signals:
  void userLocatedProject(const QUrl &url);
//  std::shared_ptr<UnrealProjectContext> contextChanged();

public slots:
  void on_LocateProjectButton_clicked();
  void onContextChanged();

private:
  Ui::MainWindow *ui;

  std::shared_ptr<UnrealProjectContext> m_context = std::make_shared<UnrealProjectContext>();

  bool validateProjectDir(const QUrl &url);
};
#endif // MAINWINDOW_H
