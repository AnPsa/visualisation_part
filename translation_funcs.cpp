#include "window.h"
#include <QMouseEvent>

void Scene3D::initializeGL()
{
  glEnable(GL_COLOR_MATERIAL);
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  qglClearColor (Qt::white);
  glEnable (GL_DEPTH_TEST);
  glShadeModel (GL_SMOOTH);
}

void Scene3D::resizeGL (int nWidth, int nHeight)
{
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  GLfloat ratio = (GLfloat)nHeight / (GLfloat)nWidth;
  glOrtho (-10.0, 10.0, -10.0 * ratio, 10.0 * ratio, -10.0, 10.0);
  glViewport (0, 0, (GLint)nWidth, (GLint)nHeight);
}


void Scene3D::mousePressEvent (QMouseEvent* pe)
{
  ptrMousePosition = pe->pos();
}

void Scene3D::mouseReleaseEvent (QMouseEvent* /*pe*/)
{
}

void Scene3D::mouseMoveEvent(QMouseEvent* pe)
{
  xRot += 180 / nSca * (GLfloat)(pe->y () - ptrMousePosition.y ()) / height ();
  zRot += 180 / nSca * (GLfloat)(pe->x () - ptrMousePosition.x ()) / width ();
  ptrMousePosition = pe->pos ();

  updateGL();
}

void Scene3D::wheelEvent(QWheelEvent* pe)
{
  if ((pe->delta()) > 0)
    scale_plus ();
  else if ((pe->delta()) < 0)
    scale_minus ();
  updateGL();
}

void Scene3D::keyPressEvent (QKeyEvent* pe)
{
  switch (pe->key())
    {
      case Qt::Key_Equal:
        scale_plus();
        break;

      case Qt::Key_Minus:
        scale_minus();
        break;

      case Qt::Key_W:
        rotate_up ();
        break;

      case Qt::Key_S:
        rotate_down ();
        break;

      case Qt::Key_A:
        rotate_left ();
        break;

      case Qt::Key_D:
          rotate_right ();
        break;

      case Qt::Key_Q:
        translate_down ();
        break;

      case Qt::Key_E:
        translate_up ();
        break;

      case Qt::Key_Space:
        defaultScene ();
        break;

      case Qt::Key_Escape:
        this->close ();
        return;
      default:
        return;
    }

  updateGL();
}

void Scene3D::scale_plus()
{
  nSca = nSca * 1.1;
}

void Scene3D::scale_minus()
{
  nSca = nSca / 1.1;
}

void Scene3D::rotate_up()
{
  xRot += 1.0;
}

void Scene3D::rotate_down()
{
  xRot -= 1.0;
}

void Scene3D::rotate_left()
{
  zRot += 1.0;
}

void Scene3D::rotate_right()
{
  zRot -= 1.0;
}

void Scene3D::translate_down()
{
  zTra -= 0.05;
}

void Scene3D::translate_up ()
{
  zTra += 0.05;
}

void Scene3D::defaultScene ()
{
  xRot = -90;
  yRot = 0;
  zRot = 0;
  zTra = 0;
  nSca = 1;
}

void Scene3D::drawAxis ()
{
  glLineWidth (3.0f);

  glBegin (GL_LINES);
  glColor3d (1, 0, 0);
  glVertex3f ( 3.0f,  0.0f,  0.0f);
  glVertex3f (-3.0f,  0.0f,  0.0f);
  glEnd ();

  QColor halfGreen (0, 128, 0, 255);
  qglColor (halfGreen);
  glBegin (GL_LINES);
  glVertex3f (0.0f,   3.0f,  0.0f);
  glVertex3f (0.0f, -10.0f,  0.0f);
  glEnd ();
}


