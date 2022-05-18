#include "UnrealProjectPluginView.h"
#include "ui_UnrealProjectPluginView.h"

namespace KPM {

UnrealProjectPluginView::UnrealProjectPluginView(QWidget *parent)
    : QWidget(parent), ui(new Ui::UnrealProjectPluginView) {
  ui->setupUi(this);
}

UnrealProjectPluginView::~UnrealProjectPluginView() { delete ui; }

void UnrealProjectPluginView::changeEvent(QEvent *e) {
  QWidget::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;
  default:
    break;
  }
}

} // namespace KPM
