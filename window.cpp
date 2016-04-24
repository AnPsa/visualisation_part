#include "window.h"

#include <QtGui>
#include <math.h>
#include <string.h>
#include <QDebug>

Scene3D::Scene3D (QWidget* parent) : QGLWidget(parent)
{
  xRot = -90; yRot = 0; zRot = 0; zTra = 0; nSca = 1;
}

Scene3D::~Scene3D ()
{
}

void Scene3D::paintGL ()
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
  drawAxis ();
  draw_H ();

  glScalef (nSca, nSca, nSca);
  glTranslatef (0.0f, zTra, 0.0f);
  glRotatef (xRot, 1.0f, 0.0f, 0.0f);
  glRotatef (yRot, 0.0f, 1.0f, 0.0f);
  glRotatef (zRot, 0.0f, 0.0f, 1.0f);
}
