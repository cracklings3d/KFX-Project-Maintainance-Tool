#ifndef KPM_USERCONF_H
#define KPM_USERCONF_H

#include "SvnConf.h"
#include "PmtConf.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QStandardPaths>
#include <QUrl>

namespace KPM {

class UserConf : public PmtConf {
  Q_OBJECT
public:
  explicit UserConf(QObject *parent = nullptr);

  virtual void deserialize(const QJsonObject &url) override;
  virtual QJsonObject serialize() const override;

signals:

public slots:
  void saveUserConf();
  void loadUserConf();

private:
  SvnConf m_SvnConf;
  QString getConfPath() const;
};

} // namespace KPM

#endif // KPM_USERCONF_H
