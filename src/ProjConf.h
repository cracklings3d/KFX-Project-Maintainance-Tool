#ifndef KPM_PROJCONF_H
#define KPM_PROJCONF_H

#include <QObject>

namespace KPM {
class ProjConf : public QObject {
  Q_OBJECT

public:
  explicit ProjConf(QObject *parent = nullptr);
  ~ProjConf();

protected:

private:
};


} // namespace KPM
#endif // KPM_PROJCONF_H
