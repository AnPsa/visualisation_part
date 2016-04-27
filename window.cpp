#include "window.h"
#include "data_holder.h"

#include <QtGui>
#include <math.h>
#include <string.h>
#include <QDebug>
#include <math.h>



graph_2d::graph_2d (QWidget *parent, data_holder *idata) : QWidget (parent)
{
  data = idata;
  left_border = -10.;
  right_border = 10.;
  scale_coeff = 1.;
}

graph_2d::~graph_2d ()
{
}

QSize graph_2d::minimumSizeHint () const
{
  return QSize (100, 100);
}

QSize graph_2d::sizeHint () const
{
  return QSize (500, 500);
}

void graph_2d::paintEvent (QPaintEvent * /* event */)
{
  QPainter painter (this);

  painter.save ();

  painter.translate (0.5 * width (), 0.5 * height ());
  painter.scale (scale_coeff * width () / (right_border - left_border), -scale_coeff * height () / 20);// / (4.0 * (max_y - min_y)));

  painter.setPen (QPen (Qt::red, 0.1));
  painter.drawLine (left_border, 0, right_border, 0);
  painter.setPen (QPen (Qt::green, 0.1));
  painter.drawLine (0, -10, 0, 10);

  draw_H (0, painter);
  painter.restore ();
}

void graph_2d::H_color (double value, int &red, int &green)
{
  double max = data->max_H;
  double min = data->min_H;
  double middle = data->middle_H;

  if (value > data->middle_H)
    {
      if (value - middle < 1e-15)
        green = 255;
      else
        {
          red = 255 * (value - middle) / (max - middle);
          green = 255 - red;
        }
    }
  else
    {
      if (middle - value < 1e-15)
        green = 255;
      else
        {
          green = 255 * (middle - value) / (middle - min);
          red = 255 - green;
        }
    }
}

void graph_2d::draw_H (int time_step_number, QPainter &painter)
{
  int dim_h = data->m_dim_h;
  std::vector <double> X = data->m_x_h;
  std::vector <double> Y = data->m_y_h;
  std::vector <double> H = data->m_H_layer[time_step_number];
  int red = 0, green = 0;
  int i = 0;
  double hx = X[1] - X[0], hy = hx;

  while (i < dim_h)
    {
      H_color (H[i], red, green);
      QColor color (red, green, 0);
      painter.setPen (QPen (color, 0.1));
      QRect h_rect (X[i], Y[i], hx, hy);
      painter.fillRect (h_rect, color);
      painter.drawRect (h_rect);
      i++;
    }
}
