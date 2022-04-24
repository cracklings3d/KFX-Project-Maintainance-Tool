#include "UserConf.h"

namespace KPM {
UserConf::UserConf(QObject *parent) : QObject{parent} {}

void UserConf::loadOrCreateUserConf(QUrl url) {
  QString path = QStandardPaths::locate(QStandardPaths::AppDataLocation, "engine-install.conf");
}

} // namespace KPM
