#include "UserConfView.h"
#include "ui_UserConfView.h"

namespace KPM {

UserConfView::UserConfView(QWidget *parent)
    : QDialog(parent), ui(new Ui::UserConfView) {
  ui->setupUi(this);
}

UserConfView::~UserConfView() { delete ui; }

void UserConfView::changeEvent(QEvent *e) {
  QWidget::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;
  default:
    break;
    }
}

void UserConfView::saveAndClose() {
  close();
}

} // namespace KPM
