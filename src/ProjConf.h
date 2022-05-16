#ifndef KPM_PROJCONF_H
#define KPM_PROJCONF_H

#include <QObject>
#include "PmtConf.h"

namespace KPM {
class UserConf;

class ProjConf : public PmtConf {
  Q_OBJECT

public:
  explicit ProjConf(QObject *parent = nullptr);
  ~ProjConf();

protected:

private:
  UserConf *m_userConf;
};


} // namespace KPM
#endif // KPM_PROJCONF_H
