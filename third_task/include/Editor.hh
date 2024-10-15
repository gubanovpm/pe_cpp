#ifndef __Editor_hh__
#define __Editor_hh__

#include <random>
#include <ctime>

#include <QWidget>
#include <QLabel>
#include <QScopedPointer>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QSpinBox>
#include <QHeaderView>
#include <QPushButton>
#include <QStringList>
#include <QColorDialog>
#include <QMessageBox>
#include <QSizePolicy>

#include <Polygon.hh>

#ifndef NMAX
#define NMAX 100
#endif

namespace Application {

class Editor final : public QWidget {
  Q_OBJECT
public:
  Editor(QWidget *parent=nullptr);
  ~Editor();
private:
  const static inline int cols = 2;
  const static inline int rows = 3;
  const static inline char *table_style = "alternate-background-color:#cdcdcd;"
                                          "background-color:#ababab;";
  const static inline int max_rnd = 255;

  std::random_device rdev;
  std::mt19937 ring;
  std::uniform_int_distribution<int> rnd_gen;
  

  QScopedPointer<QGridLayout> grid;
  QScopedPointer<QLabel> name;
  
  QScopedPointer<QSpinBox> nbox;
  QScopedPointer<QLabel> nbox_name;
  
  QScopedPointer<QTableWidget> tableV;
  
  QScopedPointer<QTableWidget> tableE;
  
  QScopedPointer<QSpinBox> vbox;
  QScopedPointer<QLabel> vbox_name;
  QScopedPointer<QSpinBox> xbox;
  QScopedPointer<QLabel> xbox_name;
  QScopedPointer<QSpinBox> ybox;
  QScopedPointer<QLabel> ybox_name;
  QScopedPointer<QPushButton> send_coord;

  QScopedPointer<QPushButton> rand_button;
  QScopedPointer<QPushButton> draw_button;

  void setup();
  void resize_tableE(const std::size_t from, const std::size_t to);

public slots:
  void send_poly(const Polygon&);

signals:
  void add_polygon(const Polygon&);
  void show_greetings();

};

}

#endif
