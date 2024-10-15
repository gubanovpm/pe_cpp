#include <Polygon.hh>

namespace Application {

Polygon::Edge::Edge(const QColor &color): color(color) {}
Polygon::Vertex::Vertex(const QPoint &point): point(point) {}

Polygon::Polygon(const std::vector<QColor> &colors, 
                 const std::vector<QPoint> &points) {
  if (colors.size() != points.size()) {
    throw std::runtime_error("colors and points count are not equals");
  }

  vv.clear(); ve.clear();
  std::size_t n = colors.size();

  for (std::size_t i = 0; i < n; ++i) {
    vv.push_back(std::make_shared<Vertex>(points[i]));
    ve.push_back(std::make_shared<Edge>  (colors[i]));
  }

  for (std::size_t i = 0; i < n; ++i) {
    vv[i]->beg = ve[i];
    vv[i]->end = ve[(i-1)%n];

    ve[i]->beg = vv[(i+1)%n];
    ve[i]->end = vv[i];
  }
}

void Polygon::draw(QPainter &painter, const int w, const int h) const {
	QPen pen; pen.setWidth(4);
  std::size_t n = vv.size();
  auto convert = [w, h](const QPoint &p) {
    return QPoint{int(float(p.x())/255*w), int(float(p.y())/255*h)};
  };

	for(size_t i = 0; i < n; ++i) {
		pen.setColor(ve[i]->color);
		painter.setPen(pen);
		painter.drawLine(convert(vv[i]->point), convert(vv[(i+1)%n]->point));
	}
}

bool Polygon::contain(const QPoint &cursor, int w, int h) const {
  QList<QPoint> plist;
  auto convert = [w, h](const QPoint &p) {
    return QPoint{int(float(p.x())/255*w), int(float(p.y())/255*h)};
  };

  for (const auto &v: vv) {
    plist.push_back(convert(v->point));
  }
  QPolygon p(plist);
  return p.containsPoint(cursor, Qt::OddEvenFill);
}

std::size_t Polygon::size() const {
  return vv.size();
}

QColor Polygon::edgeColor(const std::size_t idx) const {
  return ve[idx]->color;
}

QPoint Polygon::vertexPoint(const std::size_t idx) const {
  return vv[idx]->point;
}

void Polygon::dump() const {
  for ( std::size_t i = 0, n = vv.size(); i < n; ++i) {
    qDebug() << vv[i]->point << ve[i]->color ;
  }
}

}
