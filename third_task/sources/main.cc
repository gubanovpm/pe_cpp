#include <MainWindow.hh>

#include <QApplication>

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  Application::MainWindow window;
  window.show();
  return app.exec();
}
