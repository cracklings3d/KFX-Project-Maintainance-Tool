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

  void onSvnConfChanged(KPM::SvnConf *svn_conf);

private:
  Ui::UserConfView *ui;

  UserConf *m_data;
};

} // namespace KPM
#endif // KPM_USERCONFVIEW_H
