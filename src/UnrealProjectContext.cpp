#include <QFile>
#include <QJsonArray>
#include <QJsonObject>

#include "UnrealProjectContext.h"

void KPM::UnrealProjectContext::setProjectFile(const QUrl &url) {
  m_projectFile = url;
  if (!url.isLocalFile() || !url.isValid())
    return;
  parseDescriptor();
  emit projectFileChanged(url);
}

const QUrl &KPM::UnrealProjectContext::projectFile() const { return m_projectFile; }

void KPM::UnrealProjectContext::resetProjectFile() {
  setProjectFile({});
  emit projectFileChanged({});
}

KPM::UnrealProjectDescriptor *
KPM::UnrealProjectContext::getProjectDescriptor() {
  return &m_projectDescriptor;
}

QByteArray KPM::UnrealProjectContext::serializeDescriptor() {
  QJsonDocument j;
  QJsonObject j_root {};
  j_root["Category"] =  m_projectDescriptor.category;
  j_root["FileVersion"] = m_projectDescriptor.fileVersion;
  j_root["EngineAssociation"] = m_projectDescriptor.engineAssociation.toString();
  j_root["Description"] = m_projectDescriptor.description;
  j_root["Modules"] = QJsonArray{};
  j_root["Plugins"] = QJsonArray{};
  for (const auto &module : m_projectDescriptor.modules) {
    QJsonObject j_module;
    j_module["Type"] = module.name;
    j_module["Type"] = Utils::toString(module.type);
    j_module["LoadingPhase"] = Utils::toString(module.loadingPhase);
    j_root["Modules"].toArray().push_back(j_module);
  }
  for (const auto &plugin : m_projectDescriptor.plugins) {
    QJsonObject j_plugin;
    j_plugin["Name"] = plugin.name;
    j_plugin["Enabled"] = plugin.enabled;
//    j_plugin["SupportedTargetPlatforms"] = plugin.supportedTargetPlatforms;
    j_plugin["MarketplaceURL"] = plugin.marketplaceURL;
  }
  j.setObject(j_root);
  return j.toJson();
}

void KPM::UnrealProjectContext::testFunc() {
  emit log("SLKDJFLSDKFHKLAJHS");
}

void KPM::UnrealProjectContext::parseDescriptor() {
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

QString KPM::Utils::toString(const UnrealModuleLoadingPhase &v) {
  switch (v) {
  case KPM::UnrealModuleLoadingPhase::Default:
    return "Default";
  default:
    return "";
  }
}

QString KPM::Utils::toString(const UnrealModuleType &v) {
  switch (v) {
  case KPM::UnrealModuleType::Developer:
    return "Developer";
  case KPM::UnrealModuleType::Runtime:
    return "Runtime";
  default:
    return "";
  }
}
