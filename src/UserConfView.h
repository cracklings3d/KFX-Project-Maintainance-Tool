#ifndef KPM_USERCONFVIEW_H
#define KPM_USERCONFVIEW_H

#include "UserConf.h"
#include "QMainWindow"

#include <QStatusBar>
#include <QDialog>

namespace KPM {

namespace Ui {
class UserConfView;
}

class UserConfView : public QDialog {
  Q_OBJECT

public:
  explicit UserConfView(QMainWindow *parent = nullptr);
  ~UserConfView();

protected:
//  void changeEvent(QEvent *e);

private slots:
  void on_buttonBox_accepted();
  void on_buttonBox_rejected();

  void on_enginePluginReposText_editingFinished();
  void on_projectPluginReposText_editingFinished();
  void on_usernameText_editingFinished();
  void on_passwordText_editingFinished();

private:
  Ui::UserConfView *ui;

  UserConf *m_data;

  void syncData();
};

} // namespace KPM
#endif // KPM_USERCONFVIEW_H
