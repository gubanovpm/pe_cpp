#ifndef __mousewindow_hh__
#define __mousewindow_hh__

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPoint>
#include <QPainterPath>

#include <utility>


namespace Application {

namespace Ui {
class MouseWindow;
}

class MouseWindow final : public QWidget {
  Q_OBJECT

public:
  MouseWindow(QWidget *parent=nullptr);
  ~MouseWindow();

private:
  QScopedPointer<Ui::MouseWindow> ui;

  std::pair<QPoint, QPoint> positions;
protected:
  void mouseMoveEvent (QMouseEvent *) override;
  void mousePressEvent(QMouseEvent *) override;
  void paintEvent(QPaintEvent *) override;
};

}

#endif

