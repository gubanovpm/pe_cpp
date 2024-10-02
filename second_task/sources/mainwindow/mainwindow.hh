#ifndef __mainwindow_hh__
#define __mainwindow_hh__

#include <QMainWindow>
#include <QDebug>

#include "mousewindow/mousewindow.hh"
#include "drawwindow/drawwindow.hh"

#define APP_NAME "QtDrawSample"
#define DPREFIX "DEBUG: "

namespace Application {

namespace Ui {
class MainWindow;
}

class MainWindow final : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent=nullptr);
  ~MainWindow();

private:
  QScopedPointer<Ui::MainWindow> ui;
  QScopedPointer<DrawWindow>   draw_window;
  QScopedPointer<MouseWindow> mouse_window;

  void setup_MainWindow();
};

}

#endif
