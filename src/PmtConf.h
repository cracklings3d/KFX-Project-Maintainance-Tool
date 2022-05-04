#ifndef PMTCONF_H
#define PMTCONF_H

#include <QJsonObject>
#include <QObject>

namespace KPM {
class PmtConf : public QObject {
  Q_OBJECT

public:
  PmtConf(QObject *parent) : QObject(parent) {};

  virtual void deserialize(const QJsonObject &) = 0;
  virtual QJsonObject serialize() const = 0;
};
}; // namespace KPM

#endif // PMTCONF_H
