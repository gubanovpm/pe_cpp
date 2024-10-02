#include <QLabel>

#include "mainwindow.hh"

#include "ui_mainwindow.h"
#include "moc_mainwindow.cpp"

namespace Application {

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent), ui(new Ui::MainWindow), 
  mouse_window(new MouseWindow), draw_window(new DrawWindow)  {
    ui->setupUi(this);
    setup_MainWindow();
}

void MainWindow::setup_MainWindow() {
  setWindowTitle(APP_NAME);

  //added greetings widget
  auto greetings_widget = new QLabel(this);
  greetings_widget->setText("Hello! Please select needed option!");
  greetings_widget->setAlignment(Qt::AlignCenter);

  // add ctrl+q shortcut for exit
  addAction(ui->ActionClose);
  QObject::connect(ui->ActionClose, &QAction::triggered, this, &QCoreApplication::quit);

  // add mouse and draw widgets into SwitchLayout
  ui->SwitchLayout->addWidget(mouse_window.get());
  ui->SwitchLayout->addWidget(draw_window.get());
  ui->SwitchLayout->addWidget(greetings_widget);

  // add menu action to show needed layout
  QObject::connect(ui->openMouseWindow, &QAction::triggered, 
      [this](){
        qDebug() << DPREFIX "openMouseWindow" ;
        ui->SwitchLayout->setCurrentWidget(mouse_window.get());
        qDebug() << DPREFIX "set mouse_window as Layout";
      });
  QObject::connect( ui->openDrawWindow, &QAction::triggered,
      [this](){
        qDebug() << "openDrawWindow" ;
        ui->SwitchLayout->setCurrentWidget(draw_window.get());
        qDebug() << DPREFIX "set draw_window as Layout";
      });
  // set by default greetings widget as default
  ui->SwitchLayout->setCurrentWidget(greetings_widget);
}

MainWindow::~MainWindow() = default;

}

