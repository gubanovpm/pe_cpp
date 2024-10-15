#ifndef __RenderArea_hh__
#define __RenderArea_hh__

#include <vector>

#include <QMenu>
#include <QPoint>
#include <QDebug>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QScopedPointer>

#include <Polygon.hh>

namespace Application {

class RenderArea final : public QWidget {
  Q_OBJECT

public:
  RenderArea(QWidget *parent=nullptr);
  ~RenderArea();

  void paintEvent(QPaintEvent* event) override;

private:
  std::vector<Polygon> polys{};

  void setup();

protected:
  void mousePressEvent(QMouseEvent* event) override;

public slots:
  void add_polygon(const Polygon &);

signals:
  void show_editor();
  void send_poly(const Polygon &);

};

}

#endif
