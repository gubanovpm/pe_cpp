#include <Editor.hh>

#include "moc_Editor.cpp"

namespace Application {

Editor::Editor(QWidget *parent):
  QWidget(parent),
  grid(new QGridLayout(this)),
  name(new QLabel("Edit polygon", this)),
  nbox(new QSpinBox(this)),
  nbox_name(new QLabel("Vertex count:", this)),
  tableV(new QTableWidget(rows, cols, this)),
  tableE(new QTableWidget(rows,    1, this)),
  vbox(new QSpinBox(this)),
  vbox_name(new QLabel("RowID", this)),
  xbox(new QSpinBox(this)),
  xbox_name(new QLabel("X:", this)),
  ybox(new QSpinBox(this)),
  ybox_name(new QLabel("Y:", this)),
  send_coord(new QPushButton(this)),
  rand_button(new QPushButton(this)),
  draw_button(new QPushButton(this)),
  ring(rdev()), 
  rnd_gen(std::uniform_int_distribution<>(1, max_rnd)){
    setup();
}

Editor::~Editor() = default;

void Editor::setup() {
  // set random seed for prng
  ring.seed(::time(NULL));
  // set spinbox property
  nbox->setMinimum(rows);
  nbox->setMaximum(NMAX);
  nbox->setSingleStep(1);
  // set tableV properties
  tableV->setHorizontalHeaderLabels({"x", "y"});
  tableV->setAlternatingRowColors(true);
  tableV->setStyleSheet(table_style);
  tableV->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  tableV->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  tableV->verticalHeader()->setStretchLastSection(true);
  tableV->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
  tableV->setEditTriggers(QAbstractItemView::NoEditTriggers);
  tableV->setFocusPolicy(Qt::NoFocus);
  tableV->setSelectionMode(QAbstractItemView::NoSelection);
  // set tableE properties
  tableE->setHorizontalHeaderLabels({"Color"});
  tableE->setAlternatingRowColors(true);
  tableE->setStyleSheet(table_style);
  tableE->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  tableE->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  tableE->verticalHeader()->setStretchLastSection(true);
  tableE->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
  tableE->setFocusPolicy(Qt::NoFocus);
  tableE->setSelectionMode(QAbstractItemView::NoSelection);
  tableE->setEditTriggers(QAbstractItemView::NoEditTriggers);
  resize_tableE(0, 2);
  // add vbox for row id
  vbox->setMinimum(1);
  vbox->setMaximum(rows);
  vbox->setSingleStep(1);
  // add xbox coord
  xbox->setMinimum(0);
  xbox->setMaximum(255);
  xbox->setSingleStep(1);
  // add ybox coord
  ybox->setMinimum(0);
  ybox->setMaximum(255);
  ybox->setSingleStep(1);
  send_coord->setText("OK");
 // add buttons
  rand_button->setText("Set random coords");
  draw_button->setText("Draw polygon");
  // set size policy
  QSizePolicy spLeft(QSizePolicy::Preferred, QSizePolicy::Preferred);
	spLeft.setHorizontalStretch(5);
	nbox->setSizePolicy(spLeft);
	spLeft.setHorizontalStretch(1);
	nbox_name->setSizePolicy(spLeft);
	spLeft.setVerticalStretch(1);
  spLeft.setHorizontalStretch(0);
	tableV->setSizePolicy(spLeft);
  tableE->setSizePolicy(spLeft);
  // locate all sub widgets
  grid->addWidget(name.get(), 1, 0, 1, 7, Qt::AlignCenter);
  grid->addWidget(nbox_name.get(), 2, 0, 1, 3);
  grid->addWidget(nbox.get(), 2, 4, 1, 3);
  grid->addWidget(tableV.get(), 3, 0, 1, 7);
  grid->addWidget(tableE.get(), 4, 0, 1, 7);
  grid->addWidget(vbox_name.get(), 5, 0, 1, 1, Qt::AlignCenter);
  grid->addWidget(vbox.get(), 5, 1, 1, 1, Qt::AlignCenter);
  grid->addWidget(xbox_name.get(), 5, 2, 1, 1, Qt::AlignCenter);
  grid->addWidget(xbox.get(), 5, 3, 1, 1, Qt::AlignCenter);
  grid->addWidget(ybox_name.get(), 5, 4, 1, 1, Qt::AlignCenter);
  grid->addWidget(ybox.get(), 5, 5, 1, 1, Qt::AlignCenter);
  grid->addWidget(send_coord.get(), 5, 6, 1, 1, Qt::AlignCenter);
  grid->addWidget(rand_button.get(), 6, 0, 1, 7);
  grid->addWidget(draw_button.get(), 7, 0, 1, 7);
  // signal on change N
  connect(nbox.get(), &QSpinBox::valueChanged, 
    [this](int n) {
      qDebug() << "nbox value changed" ;
      tableV->setRowCount(n);
      vbox->setMaximum(n);
      std::size_t prev = tableE->rowCount();
      tableE->setRowCount(n);
      resize_tableE(prev-1, n-1);
    });
  // signal for generate random polygon
  connect(rand_button.get(), &QAbstractButton::clicked,
    [this]() {
      auto model = tableV->model();
      for (std::size_t i = 0, end = vbox->maximum(); i < end; ++i) {
          model->setData(model->index(i, 0), QString::number(rnd_gen(ring)));
          model->setData(model->index(i, 1), QString::number(rnd_gen(ring)));
      }
    });
  // signal for change raw by input
  connect(send_coord.get(), &QAbstractButton::clicked,
    [this]() {
      auto model = tableV->model();
      int index = vbox->value() - 1;
      model->setData(model->index(index, 0), QString::number(xbox->value()));
      model->setData(model->index(index, 1), QString::number(ybox->value()));
    });

  // connect color selection
  connect(tableE.get(), &QTableWidget::cellClicked, 
    [this](int row, int col) {
      QColorDialog colorD;
      QColor color = colorD.getColor();
      if (!color.isValid()) {
        color = Qt::black;
      }
      tableE->setItem(row, col, new QTableWidgetItem);
      tableE->item(row, col)->setBackground(color);
    });
  // connect draw button
  connect(draw_button.get(), &QAbstractButton::clicked,
    [this]() {
      std::size_t n = vbox->maximum(), flag = 1;
      std::vector<QColor> colors;
      std::vector<QPoint> points;
      QPoint t;
      for (std::size_t i = 0; i < n; ++i) {
        colors.push_back(tableE->item(i, 0)->background().color());
        auto itemVx = tableV->item(i, 0);
        auto itemVy = tableV->item(i, 1);
        if (itemVx == 0 || itemVy == 0) {
          flag = 0;
          break;
        }
        t.setX(itemVx->text().toInt());
        t.setY(itemVy->text().toInt());
        points.push_back(t);
      }
      if (!flag) {
        QMessageBox* msgbox = new QMessageBox(this);
        msgbox->setWindowTitle("Important error");
        msgbox->setText("Not all polygon fields are setted");
        msgbox->open();
      } else {
         emit add_polygon(Polygon{colors, points});
         tableV->clearContents();
         resize_tableE(0, n-1);
         emit show_greetings();
      }
    });
}

void Editor::resize_tableE(const std::size_t from, const std::size_t to) {
  for (std::size_t i = from; i < to; ++i) {
    tableE->setItem(i, 0, new QTableWidgetItem);
    QString label = QString::number(i%(to+1)+1) + QString("||") + QString::number((i+1)%(to+1)+1);
    tableE->setVerticalHeaderItem(i, new QTableWidgetItem);
    tableE->verticalHeaderItem(i)->setText(label);
    tableE->item(i, 0)->setBackground(Qt::black);
  }

  tableE->setItem(to, 0, new QTableWidgetItem);
  QString label = QString::number(to+1)+QString("||1");
  tableE->setVerticalHeaderItem(to, new QTableWidgetItem);
  tableE->verticalHeaderItem(to)->setText(label);
  tableE->item(to, 0)->setBackground(Qt::black);
}

void Editor::send_poly(const Polygon &p) {
  std::size_t n = p.size();
  nbox->setValue(n);
  resize_tableE(0, n-1);
  for (std::size_t i = 0; i < n; ++i) {
    tableE->setItem(i, 0, new QTableWidgetItem);
    tableE->item(i, 0)->setBackground(p.edgeColor(i));
    QPoint t = p.vertexPoint(i);
    tableV->setItem(i, 0, new QTableWidgetItem);
    tableV->setItem(i, 1, new QTableWidgetItem);
    tableV->item(i, 0)->setText(QString::number(t.x()));
    tableV->item(i, 1)->setText(QString::number(t.y()));
  }
}

}

