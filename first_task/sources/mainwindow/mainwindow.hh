#ifndef __mainwindow_hh_
#define __mainwindow_hh_

#include <QMainWindow>
#include <QWidget>
#include <QtGui>
#include <QVBoxLayout>
#include <QDebug>
#include <QAction>
#include <QListWidgetItem>
#include <iostream>
#include <QTextEdit>

#define APP_NAME "QtButtonSample"
#define DPREFIX "DEBUG: "

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  void setup_MainWindow();

  Ui::MainWindow *ui;

private slots:
  void postSlot();
  void checkBoxSlot();
};
#endif // __mainwindow_hh_
