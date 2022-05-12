#ifndef SVNCONF_H
#define SVNCONF_H

#include "PmtConf.h"

#include <QString>
#include <QUrl>
#include <QWidget>

namespace KPM {
class SvnConf : public PmtConf {
  Q_OBJECT

public:
  SvnConf(QObject *parent = nullptr) : PmtConf(parent) {}

  virtual QJsonObject serialize() const override;
  virtual void deserialize(const QJsonObject &) override;

  const QUrl &EnginePluginRepos() const;
  void setEnginePluginRepos(const QUrl &newEnginePluginRepos);

  const QUrl &ProjectPluginRepos() const;
  void setProjectPluginRepos(const QUrl &newProjectPluginRepos);

  const QString &Username() const;
  void setUsername(const QString &newUsername);

  const QString &Password() const;
  void setPassword(const QString &newPassword);

signals:
  void EnginePluginReposChanged();
  void ProjectPluginReposChanged();
  void UsernameChanged();
  void PasswordChanged();

private:
  QUrl m_EnginePluginRepos;
  QUrl m_ProjectPluginRepos;
  QString m_Username;
  QString m_Password;

  Q_PROPERTY(QUrl EnginePluginRepos READ EnginePluginRepos WRITE setEnginePluginRepos NOTIFY EnginePluginReposChanged)
  Q_PROPERTY(QUrl ProjectPluginRepos READ ProjectPluginRepos WRITE setProjectPluginRepos NOTIFY ProjectPluginReposChanged)
  Q_PROPERTY(QString Username READ Username WRITE setUsername NOTIFY UsernameChanged)
  Q_PROPERTY(QString Password READ Password WRITE setPassword NOTIFY PasswordChanged)
};
} // namespace KPM

#endif // SVNCONF_H
