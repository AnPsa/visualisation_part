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


    Scene3D draw_area;

    draw_area.resize (500, 500);
    draw_area.show ();
    app.exec ();
    return 0;
}
