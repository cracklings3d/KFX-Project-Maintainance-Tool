#include "UserConfView.h"
#include "ui_UserConfView.h"

namespace KPM {

UserConfView::UserConfView(QMainWindow *parent)
    : QDialog(parent), ui(new Ui::UserConfView), m_data(new UserConf(parent)) {
  ui->setupUi(this);
  m_data->loadUserConf();
}

UserConfView::~UserConfView() { delete ui; }

//void UserConfView::changeEvent(QEvent *e) {
//  QWidget::changeEvent(e);
//  switch (e->type()) {
//  case QEvent::LanguageChange:
//    ui->retranslateUi(this);
//    break;
//  default:
//    break;
//  }
//}

void UserConfView::on_buttonBox_accepted() {
  m_data->saveUserConf();

  static_cast<QMainWindow *>(parent())->statusBar()->showMessage(
      tr("User configuration saved."), 2000);

  close();
}

void UserConfView::on_buttonBox_rejected() {
  static_cast<QMainWindow *>(parent())->statusBar()->showMessage(
      tr("Configuration cancelled."), 2000);

  close();
}

void UserConfView::onSvnConfChanged(SvnConf *svn_conf) {
  m_data->setSvnConf(svn_conf);
}

} // namespace KPM
