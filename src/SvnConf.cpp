#include "SvnConf.h"

#include <QJsonObject>

namespace KPM {

QJsonObject SvnConf::serialize() const {
  QJsonObject j_conf{};
  j_conf["EnginePluginRepos"] = m_EnginePluginRepos.toString();
  j_conf["ProjectPluginRepos"] = m_ProjectPluginRepos.toString();
  j_conf["Username"] = m_Username;
  j_conf["Password"] = m_Password;
  return j_conf;
}

void SvnConf::deserialize(const QJsonObject &json) {
  if (json.contains("EnginePluginRepos")) {
    setEnginePluginRepos(QUrl{json.value("EnginePluginRepos").toString()});
  } else {
    setEnginePluginRepos(m_EnginePluginRepos);
  }

  if (json.contains("ProjectPluginRepos")) {
    setProjectPluginRepos(QUrl{json.value("ProjectPluginRepos").toString()});
  } else {
    setProjectPluginRepos(m_ProjectPluginRepos);
  }

  if (json.contains("Username")) {
    setUsername(json.value("Username").toString());
  } else {
    setUsername("");
  }

  if (json.contains("Password")) {
    setPassword(json.value("Password").toString());
  } else {
    setPassword("");
  }
}

const QUrl &SvnConf::EnginePluginRepos() const { return m_EnginePluginRepos; }
const QUrl &SvnConf::ProjectPluginRepos() const { return m_ProjectPluginRepos; }
const QString &SvnConf::Username() const { return m_Username; }
const QString &SvnConf::Password() const { return m_Password; }

void SvnConf::setEnginePluginRepos(const QUrl &newEnginePluginRepos) {
  if (m_EnginePluginRepos == newEnginePluginRepos)
    return;
  m_EnginePluginRepos = newEnginePluginRepos;
  emit EnginePluginReposChanged();
}
void SvnConf::setProjectPluginRepos(const QUrl &newProjectPluginRepos) {
  if (m_ProjectPluginRepos == newProjectPluginRepos)
    return;
  m_ProjectPluginRepos = newProjectPluginRepos;
  emit ProjectPluginReposChanged();
}
void SvnConf::setUsername(const QString &newUsername) {
  if (m_Username == newUsername)
    return;
  m_Username = newUsername;
  emit UsernameChanged();
}
void SvnConf::setPassword(const QString &newPassword) {
  if (m_Password == newPassword)
    return;
  m_Password = newPassword;
  emit PasswordChanged();
}

} // namespace KPM
