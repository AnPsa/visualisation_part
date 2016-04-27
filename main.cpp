#include "data_holder.h"
#include "window.h"
#include <fenv.h>
#include <QMainWindow>
#include <QApplication>

int main (int argc, char *argv[])
{
  QApplication app (argc, argv);

  //feenableexcept (FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW);

  QMainWindow *window = new QMainWindow;
  window->setWindowTitle ("Graph");

  data_holder data;
  data.read_data ("density_36.log", "velocity_52.log");

  graph_2d *draw_area = new graph_2d (window, &data);

  window->resize (500, 500);
  window->setCentralWidget (draw_area);
  window->show ();
  app.exec ();
  delete window;
  return 0;
}
