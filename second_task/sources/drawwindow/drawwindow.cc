#include "drawwindow.hh"

#include "moc_drawwindow.cpp"
#include "moc_render.cpp"
#include "ui_drawwindow.h"

namespace Application {

DrawWindow::DrawWindow(QWidget *parent) :
  QWidget(parent), ui(new Ui::DrawWindow), render(new Render){
  
  ui->setupUi(this);
	ui->DrawLayout->addWidget(render.get(), 0, 0, 3, 2);

	auto addItemMem = QOverload<const QString &, const QVariant &>::of(&QComboBox::addItem);
	auto addComboBox = [this, addItemMem] (const auto &elems, const auto &box, const auto &slot) {
		using namespace std::placeholders;
		std::for_each(std::begin(elems), std::end(elems), 
			[call_ = std::bind(addItemMem, box, _1, _2)] (auto &styleArgs)
			{
				std::apply(call_, styleArgs);
			}
		);
		connect(box, &QComboBox::activated, this, slot);
	};

	addComboBox(shapes, ui->shapeChoose, &DrawWindow::shapeChanged);
	addComboBox(penStyles, ui->penStyleChoose, &DrawWindow::penChanged);
	addComboBox(penCaps, ui->penCapChoose, &DrawWindow::penChanged);
	addComboBox(penJoins, ui->penJoinChoose, &DrawWindow::penChanged);
	addComboBox(brushStyles, ui->brushStyleChoose, &DrawWindow::brushChanged);

	connect(ui->penWidthChoose, &QSlider::valueChanged, this, &DrawWindow::penChanged);

	textureBrush = QBrush(QPixmap(":/texture.png").scaled({100, 100}, Qt::KeepAspectRatio));
	shapeChanged();
	penChanged();
	brushChanged();
}

void DrawWindow::shapeChanged() {
	Render::Shape shape = Render::Shape(ui->shapeChoose->itemData(
		ui->shapeChoose->currentIndex()).toInt());
	render->setShape(shape);
}

void DrawWindow::penChanged() {
	int width = ui->penWidthChoose->sliderPosition();
	Qt::PenStyle style = Qt::PenStyle(ui->penStyleChoose->itemData(
		ui->penStyleChoose->currentIndex()).toInt());
	Qt::PenCapStyle cap = Qt::PenCapStyle(ui->penCapChoose->itemData(
		ui->penCapChoose->currentIndex()).toInt());
	Qt::PenJoinStyle join = Qt::PenJoinStyle(ui->penJoinChoose->itemData(
		ui->penJoinChoose->currentIndex()).toInt());

	render->setPen(QPen(Qt::blue, width, style, cap, join));
}

void DrawWindow::brushChanged() {
  Qt::BrushStyle style = Qt::BrushStyle(ui->brushStyleChoose->itemData(ui->brushStyleChoose->currentIndex()).toInt());

	auto setupGrad = [this](auto &grad) {
		grad.setColorAt(0.0, Qt::white);
		grad.setColorAt(0.2, Qt::green);
		grad.setColorAt(1.0, Qt::black);
		render->setBrush(grad);
	};

	switch(style) {
		case Qt::LinearGradientPattern: {
			QLinearGradient linearGradient(0, 0, render->width(), render->height());
			setupGrad(linearGradient);
			break;
		}
		case Qt::RadialGradientPattern: {
			QRadialGradient radialGradient(render->width() / 2, render->height() / 2, 
				std::max(render->width() / 2, render->height() / 2), render->width() / 4, render->height() / 4);
			setupGrad(radialGradient);
			break;
		}
		case Qt::ConicalGradientPattern: {
			QConicalGradient conicalGradient(render->width() / 2, render->height() / 2, 150);
			setupGrad(conicalGradient);
			break;
		}
		case Qt::TexturePattern: {
			render->setBrush(textureBrush);
			break;
		}
		default: {
			render->setBrush(QBrush(Qt::green, style));
		}
	}
}

void DrawWindow::resizeEvent(QResizeEvent* event) {
	brushChanged();
}

DrawWindow::~DrawWindow() = default;

}
