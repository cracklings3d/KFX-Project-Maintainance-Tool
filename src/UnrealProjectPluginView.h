#ifndef KPM_UNREALPROJECTPLUGINVIEW_H
#define KPM_UNREALPROJECTPLUGINVIEW_H

#include <QWidget>

namespace KPM {

namespace Ui {
class UnrealProjectPluginView;
}

class UnrealProjectPluginView : public QWidget
{
  Q_OBJECT

public:
  explicit UnrealProjectPluginView(QWidget *parent = nullptr);
  ~UnrealProjectPluginView();

signals:
  void buttonPress();

protected:
  void changeEvent(QEvent *e);

private:
  Ui::UnrealProjectPluginView *ui;
};


} // namespace KPM
#endif // KPM_UNREALPROJECTPLUGINVIEW_H
