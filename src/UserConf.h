#ifndef KPM_USERCONF_H
#define KPM_USERCONF_H

#include "SvnConf.h"

#include <QObject>

namespace KPM {
class UserConf : public QObject {
  Q_OBJECT
public:
  explicit UserConf(QObject *parent = nullptr);

signals:

private:
  SvnConf m_SvnConf;
};

} // namespace KPM

#endif // KPM_USERCONF_H
