#ifndef SVNCONF_H
#define SVNCONF_H

#include <QWidget>

namespace KPM {
namespace Ui {
class SvnConfView;
}

class SvnConf {};

class SvnConfView : public QWidget {
  Q_OBJECT

public:
  explicit SvnConfView(QWidget *parent = nullptr);
  ~SvnConfView();

private:
  Ui::SvnConfView *ui;
};
} // namespace KPM

#endif // SVNCONF_H
