#ifndef KPM_MASTERCONF_H
#define KPM_MASTERCONF_H

#include "SvnConf.h"

#include <QObject>

namespace KPM {
class ProjectConf : public QObject {
  Q_OBJECT
public:
  explicit ProjectConf(QObject *parent = nullptr);

signals:

private:
  SvnConf m_SvnConf;
};

} // namespace KPM

#endif // KPM_MASTERCONF_H
