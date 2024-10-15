#include <MainWindow.hh>

#include "moc_MainWindow.cpp"

namespace Application {

MainWindow::MainWindow(QWidget *parent): 
  QMainWindow(parent), 
  close_shortcut(new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q), this)),
  central(new QWidget(this)), 
  switcher(new QStackedWidget(this)),
  greetings(new QLabel(this)),
  editor(new Editor(this)),
  render_area(new RenderArea(this))  {
    setup();
}

MainWindow::~MainWindow() = default;

void MainWindow::setup() {
  setWindowTitle(APP_NAME);
  central->setGeometry(0, 0, WIDTH, HEIGHT);
  QGridLayout *grid = new QGridLayout(this);

  switcher->addWidget(greetings.get());
  switcher->addWidget(editor.get());
  greetings->setText("Hello there!\n\rQuit: ctrl+q\n\rUse left click in the left section to edit polygon");
  greetings->setAlignment(Qt::AlignCenter);
  switcher->setCurrentWidget(greetings.get());

  // set sizes of render area and editor
  grid->addWidget(render_area.get(), 0, 0);
  grid->addWidget(switcher.get(), 0, 1);
  grid->setColumnStretch(0, 4);
  grid->setColumnStretch(1, 1);

  central->setLayout(grid);
  setCentralWidget(central.get());

  // connection for sending and drawing polygon
  connect(editor.get(), SIGNAL (add_polygon(const Polygon&)),
          render_area.get(), SLOT(add_polygon(const Polygon&)));
  // add ctrl+q action for exit
  connect(close_shortcut.get(), &QShortcut::activated, 
          this, &QCoreApplication::quit);

  connect(render_area.get(), SIGNAL(show_editor()),
          this, SLOT(show_editor()));

  connect(editor.get(), SIGNAL(show_greetings()),
          this, SLOT(show_greetings()));

  connect(render_area.get(), SIGNAL(send_poly(const Polygon&)),
          editor.get(), SLOT(send_poly(const Polygon&)));
}

void MainWindow::show_editor() {
  switcher->setCurrentWidget(editor.get());
}

void MainWindow::show_greetings() {
  switcher->setCurrentWidget(greetings.get());
}

}
