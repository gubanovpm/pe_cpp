#include <RenderArea.hh>

#include "moc_RenderArea.cpp"

namespace Application {

RenderArea::RenderArea(QWidget *parent) :
  QWidget(parent) {
    setup();
}

RenderArea::~RenderArea() = default;

void RenderArea::setup() {
}

void RenderArea::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  painter.drawRoundedRect(2,2,width()-5, height()-5,2,2);
  for (const auto &p: polys) {
    p.dump();
    p.draw(painter, width(), height());
  }
}

void RenderArea::mousePressEvent(QMouseEvent* event) {
	if (event->button()==Qt::LeftButton) {
    auto up = polys.end();
    for (auto cur = polys.begin(), end = polys.end(); cur != end; ++cur) {
      if(cur->contain(event->pos(), width(), height())) {
        up = cur;
      }
    }
    if(up != polys.end()) {
      emit send_poly(*up);
    }
    emit show_editor();
  }			
}

void RenderArea::add_polygon(const Polygon &p) {
  polys.push_back(p);
  update();
}

}

