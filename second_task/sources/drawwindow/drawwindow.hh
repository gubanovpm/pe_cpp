#ifndef __drawwindow_hh__
#define __drawwindow_hh__

#include <tuple>
#include <functional>

#include <QWidget>
#include "render.hh"

namespace Application {

namespace Ui {
class DrawWindow;
}

class DrawWindow final : public QWidget {
  Q_OBJECT

public:
  DrawWindow(QWidget *parent=nullptr);
  ~DrawWindow();

public slots:
  void shapeChanged();
  void penChanged();
  void brushChanged();

private:
  QScopedPointer<Ui::DrawWindow> ui;
	QScopedPointer<Render> render;
	QBrush textureBrush;

	void resizeEvent(QResizeEvent* event) override;

	using ArgType =  std::tuple<const char *, const int>;
	constexpr static inline ArgType penStyles[] = {
		{"Solid", Qt::SolidLine},
		{"Dash", Qt::DashLine},
		{"Dot", Qt::DotLine},
		{"Dash Dot", Qt::DashDotLine},
		{"Dash Dot Dot", Qt::DashDotDotLine},
		{"None", Qt::NoPen}
	};

	constexpr static inline ArgType shapes[] = {
		{"Polygon", Render::Polygon},
		{"Rectangle", Render::Rect},
		{"Rounded Rectangle", Render::RoundedRect},
		{"Ellipse", Render::Ellipse},
		{"Custom", Render::Custom}
	};

	constexpr static inline ArgType penCaps[] = {
		{"Flat", Qt::FlatCap},
		{"Square", Qt::SquareCap},
		{"Round", Qt::RoundCap}
	};

	constexpr static inline ArgType penJoins[] = {
		{"Miter", Qt::MiterJoin},
		{"Bevel", Qt::BevelJoin},
		{"Round", Qt::RoundJoin}
	};

	constexpr static inline ArgType brushStyles[] = {
		{"Linear Gradient", Qt::LinearGradientPattern},
		{"Radial Gradient", Qt::RadialGradientPattern},
		{"Conical Gradient", Qt::ConicalGradientPattern},
		{"Texture", Qt::TexturePattern},
		{"Solid", Qt::SolidPattern},
		{"Horizontal", Qt::HorPattern},
		{"Vertical", Qt::VerPattern},
		{"Cross", Qt::CrossPattern},
		{"Backward Diagonal", Qt::BDiagPattern},
		{"Forward Diagonal", Qt::FDiagPattern},
		{"Diagonal Cross", Qt::DiagCrossPattern},
		{"Dense 1", Qt::Dense1Pattern},
		{"Dense 2", Qt::Dense2Pattern},
		{"Dense 3", Qt::Dense3Pattern},
		{"Dense 4", Qt::Dense4Pattern},
		{"Dense 5", Qt::Dense5Pattern},
		{"Dense 6", Qt::Dense6Pattern},
		{"Dense 7", Qt::Dense7Pattern},
		{"None", Qt::NoBrush}
	};

};

}

#endif

