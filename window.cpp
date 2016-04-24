#include "window.h"

#include <QtGui>
#include <math.h>
#include <string.h>
#include <QDebug>

Scene3D::Scene3D (QWidget* parent, data_holder *idata) : QGLWidget(parent)
{

  data = idata;
  xRot = -90; yRot = 0; zRot = 0; zTra = 0; nSca = 0.1;
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
  draw_H (0);

  glScalef (nSca, nSca, nSca);
  glTranslatef (0.0f, zTra, 0.0f);
  glRotatef (xRot, 1.0f, 0.0f, 0.0f);
  glRotatef (yRot, 0.0f, 1.0f, 0.0f);
  glRotatef (zRot, 0.0f, 0.0f, 1.0f);
}


void Scene3D::H_color (double value)
{
  double max = data->max_H;
  double min = data->min_H;
  double middle = data->middle_H;

  float red = 0, green = 0, blue = 0;
  if (value > data->middle_H)
    {
      if (value - middle < 1e-15)
        green = 1;
      else
        {
          green = (max - middle) / (value - middle);
          red = 1 - green;
        }
    }
  else
    {
      if (middle - value < 1e-15)
        green = 1;
      else
        {
          green = (middle - min) / (middle - value);
          blue = 1 - green;
        }
    }
  glColor3d (red, green, blue);
}

void Scene3D::draw_H (int time_step_number)
{

  int dim_h = data->m_dim_h;
  std::vector <double> X = data->m_x_h;
  std::vector <double> Y = data->m_y_h;
  std::vector <int> M0R = data->m_h_M0R;
  std::vector <double> H = data->m_H_layer[time_step_number];
  int i = 0;

  while (i < dim_h + 1)
    {
      if (Y[i] > Y[i + 1])
        {
          return;
        }
      if (X[i] > X[i + 1])
      {
          i++;
        }
      glBegin (GL_POLYGON);
      H_color (H[i]);
      glVertex3f (X[i], Y[i], 0);
      H_color (H[i+1]);
      glVertex3f (X[i + 1], Y[i], 0);
      H_color (H[M0R[i] + 1]);
      glVertex3f (X[i + 1], Y[M0R[i] + 1], 0);
      H_color (H[M0R[i]]);
      glVertex3f (X[i], Y[M0R[i] + 1], 0);
      glEnd ();
      i++;

    }
  glEnd ();
}
