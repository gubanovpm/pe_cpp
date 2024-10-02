#ifndef __render_hh__
#define __render_hh__

#include <QWidget>
#include <QScopedPointer>
#include <QPainterPath>
#include <QPainter>
#include <QPen>
#include <QBrush>

class Render final : public QWidget {
    Q_OBJECT

public:
	enum Shape {
		Polygon,
		Rect,
		RoundedRect,
		Ellipse,
		Custom
	};

  Render(QWidget *parent = 0);
  ~Render();

	void setShape(Shape new_shape);
	void setPen(const QPen &new_pen);
	void setBrush(const QBrush &new_brush);

	void paintEvent(QPaintEvent* event) override;

private:
	Shape shape_ = Polygon;
	QPen pen_;
	QBrush brush_;
};

#endif
