#ifndef __MainWindow_hh__
#define __MainWindow_hh__

#include <QCoreApplication>
#include <QGridLayout>
#include <QShortcut>
#include <QMainWindow>
#include <QDebug>
#include <QPainter>
#include <QStackedWidget>

#include <Editor.hh>
#include <RenderArea.hh>

#include <Polygon.hh>

#define APP_NAME "polygon"

#ifndef WIDTH
#define WIDTH 640
#endif
#ifndef HEIGHT
#define HEIGHT 480
#endif


namespace Application {

class MainWindow final : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent=nullptr);
  ~MainWindow();

public slots:
  void show_editor();
  void show_greetings();

private:
  void setup();

  QScopedPointer<QShortcut> close_shortcut;

  QScopedPointer<QWidget> central;
  
  QScopedPointer<QStackedWidget> switcher;
  QScopedPointer<QLabel> greetings;
  QScopedPointer<Editor> editor;
  
  QScopedPointer<RenderArea> render_area;
};

}

#endif
