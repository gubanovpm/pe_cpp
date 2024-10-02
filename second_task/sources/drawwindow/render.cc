#include "render.hh"

Render::Render(QWidget *parent) :
    QWidget(parent) {
	setBackgroundRole(QPalette::Base);
  setAutoFillBackground(true);
}

void Render::setShape(Shape new_shape) {
	shape_ = new_shape;
	update();
}

void Render::setPen(const QPen &new_pen) {
	pen_ = new_pen;
	update();
}

void Render::setBrush(const QBrush &new_brush) {
	brush_ = new_brush;
	update();
}

Render::~Render() = default;

void Render::paintEvent(QPaintEvent* event) {
	qDebug() << "In paint event multimedia " << width() << height();

  QPainter p(this);
	p.setPen(pen_);
	p.setBrush(brush_);
	switch (shape_) {
		case Polygon: {
			const QPoint points[] = {
				QPoint(0.1 * width(), 0.8 * height()),
				QPoint(0.05 * width(), 0.4 * height()),
				QPoint(0.2 * width(), 0.1 * height()),
				QPoint(0.6 * width(), 0.1 * height()),
				QPoint(0.8 * width(), 0.3 * height()),
				QPoint(0.9 * width(), 0.5 * height()),
				QPoint(0.9 * width(), 0.7 * height()),
				QPoint(0.4 * width(), 0.9 * height())
			};
			p.drawPolygon(points, sizeof(points)/sizeof(QPoint));
			break;
		}
		case Rect: {
			QRect rect(10, 10, width() - 20, height() - 20);
			p.drawRect(rect);
			break;
		}
		case RoundedRect: {
			QRect rect(10, 10, width() - 20, height() - 20);
			p.drawRoundedRect(rect, 25, 25, Qt::RelativeSize);
			break;
		}
		case Ellipse: {
			QRect rect(10, 10, width() - 20, height() - 20);
			p.drawEllipse(rect);
			break;
		}
		case Custom: {
			QPainterPath path;
			path.moveTo(width() - 10, height() - 10);
			path.lineTo(10, height() - 10);
			path.lineTo(10, 10);
			path.cubicTo(0.3 * width(), 2.2 * height(), 0.7 * width(), -0.9 * height(), width() - 10, height() - 10);
			p.drawPath(path);
			break;
		}
		default:;
	}
}
