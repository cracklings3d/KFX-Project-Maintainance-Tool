#ifndef KPM_UNREALPROJECTCONTEXT_H
#define KPM_UNREALPROJECTCONTEXT_H

#include <QJsonDocument>
#include <QObject>
#include <QUrl>
#include <QVector>
#include <QVersionNumber>

namespace KPM {
enum class UnrealModuleType {
  Runtime,
  Developer,
};

enum class UnrealModuleLoadingPhase {
  Default,
};

enum class UnrealPlatform{
  Win32 = 0x01,
  Win64 = 0x02,
  Mac = 0x04,
  Linux = 0x08
};

struct UnrealModuleDescriptor {
  QString name;
  UnrealModuleType type;
  UnrealModuleLoadingPhase loadingPhase;
};

struct UnrealPluginDescriptor {
  QString name;
  bool enabled;
  QVector<UnrealPlatform> supportedTargetPlatforms;
  QString marketplaceURL;
};

struct UnrealProjectDescriptor {
public:
  int fileVersion;
  QVersionNumber engineAssociation;
  QString category;
  QString description;
  QVector<UnrealModuleDescriptor> modules;
  QVector<UnrealPluginDescriptor> plugins;
};

class UnrealProjectContext : public QObject {
  Q_OBJECT

public:
  UnrealProjectContext(QObject *parent = nullptr) : QObject(parent) {}

  void setProjectFile(const QUrl &url);
  const QUrl &projectFile() const;
  void resetProjectFile();

  UnrealProjectDescriptor *getProjectDescriptor();
  QByteArray serializeDescriptor();

signals:
  void projectFileChanged(QUrl);

private:
  QUrl m_projectFile;
  UnrealProjectDescriptor m_projectDescriptor;

  QJsonDocument m_descriptorCache;

  void parseDescriptor();

};

class Utils {
public:
  static QString toString(const UnrealModuleLoadingPhase &v);
  static QString toString(const UnrealModuleType &v);
};
} // namespace KPM

#endif // KPM_UNREALPROJECTCONTEXT_H
