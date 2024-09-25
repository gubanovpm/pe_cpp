#include "mainwindow.hh"

#include "moc_mainwindow.cpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : 
  QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setup_MainWindow();
}

MainWindow::~MainWindow() { 
  delete ui; 
}

void MainWindow::setup_MainWindow() {
  setWindowTitle(APP_NAME);
  
  setCentralWidget(ui->layoutWidget);

  QObject::connect(ui->YoButton, &QAbstractButton::clicked,
    [](){ 
      std::cout << "Yoo" << std::endl;
      qDebug() << DPREFIX"printed \"Yoo\" into stdout";
    });

  QObject::connect(ui->SubmitButton, &QAbstractButton::clicked,
      this, &MainWindow::postSlot);
  
  ui->CheckBoxButton->setCheckable(true);
  QObject::connect(ui->CheckBoxButton, &QAbstractButton::clicked,
      this, &MainWindow::checkBoxSlot);
}

void MainWindow::postSlot() {
  qDebug() << DPREFIX"call postSlot" ;
 
  QString getText = ui->inputTextField->toPlainText();
  qDebug() << DPREFIX"get string from input:" << getText ;
  ui->outputTextField->setText(getText);
  qDebug() << DPREFIX"put string from input to output";
  ui->CheckBoxButton->setChecked(false);
  qDebug() << DPREFIX"CheckBoxButton setChecked=false";
}

void MainWindow::checkBoxSlot() {
  qDebug() << DPREFIX"call checkBoxSlot";
  ui->CheckBoxButton->setChecked(true);
  qDebug() << DPREFIX"CheckBoxButton setChecked=true";
}

