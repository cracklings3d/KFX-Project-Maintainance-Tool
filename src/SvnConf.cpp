#include "SvnConf.h"
#include "ui_SvnConf.h"

KPM::SvnConfView::SvnConfView(QWidget *parent)
    : QWidget(parent), ui(new Ui::SvnConfView) {
  ui->setupUi(this);
}

KPM::SvnConfView::~SvnConfView() { delete ui; }
