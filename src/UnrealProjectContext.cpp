#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "UnrealProjectContext.h"

void KPM::UnrealProjectContext::setProjectFile(const QUrl &url) {
  m_projectFile = url;
  if (!url.isLocalFile() || !url.isValid())
    return;
  parseProject();
  emit projectFileChanged(url);
}

const QUrl &KPM::UnrealProjectContext::projectFile() const { return m_projectFile; }

void KPM::UnrealProjectContext::resetProjectFile() {
  setProjectFile({});
  emit projectFileChanged({});
}

void KPM::UnrealProjectContext::parseProject() {
  QFile f {m_projectFile.toLocalFile()};
  f.open(QFile::OpenModeFlag::ReadOnly);
  assert(f.isOpen());

  QJsonDocument j;
  const auto f_str = f.readAll();
  j = QJsonDocument::fromJson(f_str);

  m_projectDescriptor.fileVersion = j["FileVersion"].toInt();
  m_projectDescriptor.engineAssociation = QVersionNumber::fromString(j["EngineAssociation"].toString());
  m_projectDescriptor.category = j["Category"].toString();
  m_projectDescriptor.description = j["Description"].toString();

  QJsonArray j_modules = j["Modules"].toArray();
  for (auto j_module : j_modules) {
    UnrealModuleDescriptor module;

    module.name = j_module.toObject()["Name"].toString();

    if (j_module.toObject()["Type"].toString() == "Runtime")
      module.type = UnrealModuleType::Runtime;
    if (j_module.toObject()["Type"].toString() == "Developer")
      module.type = UnrealModuleType::Developer;

    if (j_module.toObject()["LoadingPhase"] == "Default")
      module.loadingPhase = UnrealModuleLoadingPhase::Default;

    m_projectDescriptor.modules.push_back(module);
  }

  QJsonArray j_plugins = j["Plugins"].toArray();
  for (auto j_plugin : j_plugins) {
    UnrealPluginDescriptor plugin;

    plugin.name = j_plugin.toObject()["Name"].toString();

    m_projectDescriptor.plugins.push_back(plugin);
  }
}
