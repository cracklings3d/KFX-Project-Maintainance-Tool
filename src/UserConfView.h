#ifndef KPM_USERCONFVIEW_H
#define KPM_USERCONFVIEW_H

#include "UserConf.h"

#include <QDialog>

namespace KPM {

namespace Ui {
class UserConfView;
}

class UserConfView : public QDialog {
  Q_OBJECT

public:
  explicit UserConfView(QWidget *parent = nullptr);
  ~UserConfView();

protected:
  void changeEvent(QEvent *e);

private slots:
  void saveAndClose();

private:
  Ui::UserConfView *ui;

  UserConf *m_data;
};

} // namespace KPM
#endif // KPM_USERCONFVIEW_H
