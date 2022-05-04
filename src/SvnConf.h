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
  SvnConf(QObject *parent) : PmtConf(parent) {}

  virtual QJsonObject serialize() const override;
  virtual void deserialize(const QJsonObject &) override;

  const QUrl &Repos() const;
  void setRepos(const QUrl &newRepos);

  const QString &Username() const;
  void setUsername(const QString &newUsername);

  const QString &Password() const;
  void setPassword(const QString &newPassword);

signals:
  void ReposChanged();
  void UsernameChanged();
  void PasswordChanged();

private:
  QUrl m_Repos;
  QString m_Username;
  QString m_Password;
  Q_PROPERTY(QUrl Repos READ Repos WRITE setRepos NOTIFY ReposChanged)
  Q_PROPERTY(QString Username READ Username WRITE setUsername NOTIFY UsernameChanged)
  Q_PROPERTY(QString Password READ Password WRITE setPassword NOTIFY PasswordChanged)
};
} // namespace KPM

#endif // SVNCONF_H
