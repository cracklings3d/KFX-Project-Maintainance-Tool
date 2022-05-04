#pragma optimize("", off)

#include "UserConf.h"

namespace KPM {
UserConf::UserConf(QObject *parent) : PmtConf{parent}, m_SvnConf(parent) {}

void UserConf::deserialize(const QJsonObject &json) {
  //  QString path = getConfPath();
}

QJsonObject UserConf::serialize() const {
  QJsonObject j_conf{};
  j_conf["SvnConf"] = m_SvnConf.serialize();
  return j_conf;
}

void UserConf::saveUserConf() {
  QJsonObject j_obj = serialize();
  QByteArray j_buf = QJsonDocument{j_obj}.toJson(QJsonDocument::Compact);
  QFile f{getConfPath()};
  f.open(QFile::WriteOnly);
  f.write(j_buf);
}

void UserConf::loadUserConf() {
  QFile f{getConfPath()};
  f.open(QFile::OpenModeFlag::ExistingOnly);
  QJsonDocument j_doc;
  if (f.isOpen()) {
    j_doc = j_doc.fromJson(f.readAll());
  }
  const auto j_svnConf = j_doc["SvnConf"];
  if (!(j_svnConf.isNull() || j_svnConf.isUndefined())) {
    m_SvnConf.deserialize(j_svnConf.toObject());
  }
}

const SvnConf &UserConf::SvnConf() const { return m_SvnConf; }

void UserConf::setSvnConf(const SvnConf &newSvnConf) {
  if (m_SvnConf == newSvnConf)
    return;
  m_SvnConf = newSvnConf;
  emit SvnConfChanged();
}

QString UserConf::getConfPath() const {
  return QStandardPaths::locate(QStandardPaths::AppDataLocation,
                                "engine-install.conf");
}

} // namespace KPM

#pragma optimize("", on)
