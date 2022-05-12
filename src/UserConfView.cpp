#include "UserConfView.h"
#include "ui_UserConfView.h"

namespace KPM {

UserConfView::UserConfView(QMainWindow *parent)
    : QDialog(parent), ui(new Ui::UserConfView), m_data(new UserConf(parent)) {
  ui->setupUi(this);
  m_data->loadUserConf();
  syncData();
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

void UserConfView::syncData() {
  assert(m_data);

  ui->projectPluginReposText->setText(m_data->svnConf->ProjectPluginRepos().toString());
  ui->enginePluginReposText->setText(m_data->svnConf->EnginePluginRepos().toString());
  ui->usernameText->setText(m_data->svnConf->Username());
  ui->passwordText->setText(m_data->svnConf->Password());
}

void UserConfView::on_enginePluginReposText_editingFinished() {
  m_data->svnConf->setEnginePluginRepos(ui->enginePluginReposText->text());
}

void UserConfView::on_projectPluginReposText_editingFinished() {
  m_data->svnConf->setProjectPluginRepos(ui->projectPluginReposText->text());
}

void UserConfView::on_usernameText_editingFinished() {
  m_data->svnConf->setUsername(ui->usernameText->text());
}

void UserConfView::on_passwordText_editingFinished() {
  m_data->svnConf->setPassword(ui->passwordText->text());
}
} // namespace KPM
