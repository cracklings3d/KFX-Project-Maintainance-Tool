#include <QDir>

#include "UserConf.h"

namespace KPM {
UserConf::UserConf(QObject *parent)
    : PmtConf{parent}, svnConf(new SvnConf(parent)) {}

void UserConf::deserialize(const QJsonObject &json) {
  //  QString path = getConfPath();
}

QJsonObject UserConf::serialize() const {
  QJsonObject j_conf{};
  j_conf["SvnConf"] = svnConf->serialize();
  return j_conf;
}

void UserConf::saveUserConf() {
  QJsonObject j_obj = serialize();
  QByteArray j_buf = QJsonDocument{j_obj}.toJson(QJsonDocument::Compact);
  const QString conf_path = confPath();
  QFile f{conf_path};
  f.open(QIODevice::OpenModeFlag::ReadWrite);
  if (f.isOpen()) {
    f.write(j_buf);
    const auto err = f.errorString();
    f.close();
  }
}

void UserConf::loadUserConf() {
  QFile f{confPath()};
  f.open(QIODevice::ExistingOnly);
  QJsonDocument j_doc;
  if (f.isOpen()) {
    j_doc = j_doc.fromJson(f.readAll());
  }
  const auto j_svnConf = j_doc["SvnConf"];
  if (!(j_svnConf.isNull() || j_svnConf.isUndefined())) {
    svnConf->deserialize(j_svnConf.toObject());
  }
}

QString UserConf::confPath() const {
  QDir app_data_dir =
      QStandardPaths::standardLocations(QStandardPaths::AppDataLocation)[0];
  if (!app_data_dir.exists()) {
    app_data_dir.mkpath(".");
  }
  return QStandardPaths::standardLocations(QStandardPaths::AppDataLocation)[0] +
         "/engine-install.conf";
}

} // namespace KPM
