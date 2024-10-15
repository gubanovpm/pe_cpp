#ifndef __Polygon_hh__
#define __Polygon_hh__

#include <QList>
#include <QPolygon>
#include <QColor>
#include <QPoint>
#include <QDebug>
#include <QPainter>

#include <vector>
#include <memory>

namespace Application {

class Polygon final {
public:
  struct Edge; 
  struct Vertex;

  Polygon(const std::vector<QColor> &, const std::vector<QPoint> &);
  void draw(QPainter &painter, const int w, const int h) const;
  bool contain(const QPoint &cursor, const int w, const int h) const;

  std::size_t size() const;
  QColor edgeColor(const std::size_t) const;
  QPoint vertexPoint(const std::size_t) const;

  void dump() const;
private:
  std::vector<std::shared_ptr<Vertex>> vv;
  std::vector<std::shared_ptr<Edge>>   ve;
};

struct Polygon::Edge final{
  std::weak_ptr<Vertex> beg;
  std::weak_ptr<Vertex> end;
  QColor color;

  Edge(const QColor &);
};

struct Polygon::Vertex final {
  std::weak_ptr<Edge> beg;
  std::weak_ptr<Edge> end;
  QPoint point;

  Vertex(const QPoint &);
};

}

#endif
