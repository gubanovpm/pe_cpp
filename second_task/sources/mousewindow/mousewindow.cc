#include "mousewindow.hh"

#include "moc_mousewindow.cpp"
#include "ui_mousewindow.h"

namespace Application {

MouseWindow::MouseWindow(QWidget *parent) :
  QWidget(parent), ui(new Ui::MouseWindow) {
    ui->setupUi(this);
    ui->rtposition_name->setAttribute(Qt::WA_TransparentForMouseEvents);
	  ui->rtposition->setAttribute(Qt::WA_TransparentForMouseEvents);
	  ui->clickedposition_name->setAttribute(Qt::WA_TransparentForMouseEvents);
	  ui->clickedposition->setAttribute(Qt::WA_TransparentForMouseEvents);

    setMouseTracking(true);

    positions = {QPoint{0, 0}, QPoint{0, 0}};
}

MouseWindow::~MouseWindow() = default;

void MouseWindow::mouseMoveEvent(QMouseEvent *event) {
  qDebug() << "mouseMoveEvent" ;
  positions.first = event->pos();
  qDebug() << "Positions: " << positions.first ;
  ui->rtposition->setText(QString("X: %1, Y: %2").arg(event->pos().x()).arg(event->pos().y()));
  update();
}

void MouseWindow::mousePressEvent(QMouseEvent *event) {
  qDebug() << "mousePressEvent" ;
  if (event->button() == Qt::LeftButton){
    positions.second = event->pos();
    ui->clickedposition->setText(QString("X: %1, Y: %2").arg(event->pos().x()).arg(event->pos().y()));
    update();
	}
}

void MouseWindow::paintEvent(QPaintEvent* event) {
	qDebug() << "In paint event " << width() << height();

  int x, y;

  QPainter p(this);
	p.setPen(Qt::blue);

  x = positions.second.x(); y = positions.second.y();
	p.drawLine(x, y, x, 0.02 * height());
	p.drawLine(x, y, 0.02 * width(), y);

	p.setPen(Qt::red);
  x = positions.first.x(); y = positions.first.y();
	p.drawLine(x, y, x, 0.02 * height());
	p.drawLine(x, y, 0.02 * width(), y);

	p.setPen(Qt::black);
	p.drawLine(0,  0.02 * height(), 0.99 * width(), 0.02 * height());
	QPainterPath path;
	path.moveTo(width(), 0.02 * height());
	path.lineTo(0.98 * width(), 0.01 * height());
	path.lineTo(0.98 * width(), 0.03 * height());
	p.fillPath(path, QBrush(Qt::black));
	path.clear();

  p.drawLine(0.02 * width(), 0, 0.02 * width(), 0.99 * height());
	path.moveTo(0.02 * width(), height());
	path.lineTo(0.01 * width(), 0.98 * height());
	path.lineTo(0.03 * width(), 0.98 * height());
	p.fillPath(path, QBrush(Qt::black));
}

}
