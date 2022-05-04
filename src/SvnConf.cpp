#include "SvnConf.h"

#include <QJsonObject>

namespace KPM {

QJsonObject SvnConf::serialize() const {
  QJsonObject j_conf{};
  j_conf["Repos"] = m_Repos.toString();
  j_conf["Username"] = m_Username;
  j_conf["Password"] = m_Password;
  return j_conf;
}

void SvnConf::deserialize(const QJsonObject &json) {
  if (json.contains("Repos")) {
      setRepos(QUrl{json.value("Repos").toString()});
  } else {
    m_Repos = "";
  }

  if (json.contains("Username")) {
      setUsername(json.value("Username").toString());
  } else {
    m_Username = "";
  }

  if (json.contains("Password")) {
      setPassword(json.value("Password").toString());
  } else {
    m_Password = "";
  }
}

const QUrl &SvnConf::Repos() const { return m_Repos; }

void SvnConf::setRepos(const QUrl &newRepos) {
  if (m_Repos == newRepos)
    return;
  m_Repos = newRepos;
  emit ReposChanged();
}

const QString &SvnConf::Username() const { return m_Username; }

void SvnConf::setUsername(const QString &newUsername) {
  if (m_Username == newUsername)
    return;
  m_Username = newUsername;
  emit UsernameChanged();
}

const QString &SvnConf::Password() const { return m_Password; }

void SvnConf::setPassword(const QString &newPassword) {
  if (m_Password == newPassword)
    return;
  m_Password = newPassword;
  emit PasswordChanged();
}

} // namespace KPM
