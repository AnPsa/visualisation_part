#include "window.h"
#include "data_holder.h"

#include <math.h>
#include <string.h>
#include <unistd.h>

#include <QtGui>
#include <QDebug>

#define EPS 1e-6
#define ALPHA 0.5

static double solve_sqr_equation_less_root (double p, double q, double r)
{
  return (-q - sqrt (q * q - 4 * p * r)) / (2 * p);
}

static double solve_sqr_equation_more_root (double p, double q, double r)
{
  return (-q + sqrt (q * q - 4 * p * r)) / (2 * p);
}

static void calculate_vect_arrow (double k, double len_vect, double y_begin, double x_end, double y_end, double &x_vect, double &y_vect)
{
  double b = 0, p = 0, q = 0, r = 0;
  b = y_end - k * x_end;

  p = 1 + k * k;
  q = 2 * (k * b - x_end - k * y_end);
  r = x_end * x_end + (y_end - b) * (y_end - b) - len_vect * len_vect;

  if (y_begin < y_end)
    x_vect = solve_sqr_equation_less_root (p, q, r);
  else
    x_vect = solve_sqr_equation_more_root (p, q, r);
  y_vect = k * x_vect + b;
}

static void calculate_vector_coords (double v1, double v2, double x_begin, double y_begin,
                                     double &x_end, double &y_end, double &x_vect_l, double &y_vect_l,
                                     double &x_vect_r, double &y_vect_r)
{
  x_end = x_begin;
  y_end = y_begin;
  if (fabs (v1) > EPS)
    x_end = x_begin + v1;
  if (fabs (v2) > EPS)
    y_end = y_begin + v2;

  double ctg_phi = (y_end - y_begin) / (x_end - x_begin), ctg_alpha = 1. / tan (ALPHA);
  double len_vect = (sqrt ((x_end - x_begin) * (x_end - x_begin) + (y_end - y_begin) * (y_end - y_begin))) / 5;
  double k = 0;

  //right
  k = (ctg_phi * ctg_alpha - 1) / (ctg_phi + ctg_alpha);
  calculate_vect_arrow (k, len_vect, y_begin, x_end, y_end, x_vect_r, y_vect_r);

  //left
  k = (ctg_phi * ctg_alpha + 1) / (ctg_alpha - ctg_phi);
  calculate_vect_arrow (k, len_vect, y_begin, x_end, y_end, x_vect_l, y_vect_l);
}

graph_2d::graph_2d (QWidget *parent, data_holder *idata) : QWidget (parent)
{
  m_data = idata;
  m_left_border = -10.;
  m_right_border = 10.;
  m_scale_coeff = 2.;
  m_step_number = 0;
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

void graph_2d::H_color (double value, int &red, int &green)
{
  double max = m_data->max_H;
  double min = m_data->min_H;
  double middle = m_data->middle_H;

  if (value > m_data->middle_H)
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
  int dim_h = m_data->m_dim_h;
  std::vector <double> X = m_data->m_x_h;
  std::vector <double> Y = m_data->m_y_h;
  std::vector <double> H = m_data->m_H_layer[time_step_number];
  int red = 255, green = 0;
  int i = 0;
  double hx = X[1] - X[0], hy = hx;

  while (i < dim_h)
    {
      H_color (H[i], red, green);
      QColor color (red, green, 0, 180);
      painter.setPen (QPen (color, 0.01));
      QRectF h_rect (X[i], Y[i], hx, hy);
      painter.fillRect (h_rect, color);
      painter.drawRect (h_rect);
      i++;
    }
}

void graph_2d::draw_V (int time_step_number, QPainter &painter)
{
  int dim_v = m_data->m_dim_v;
  double x_vect_l = 0, y_vect_l = 0, x_vect_r = 0, y_vect_r = 0;
  for (int i = 0; i < dim_v; i++)
    {
      double x_begin = m_data->m_x_v[i], y_begin = m_data->m_y_v[i];
      double x_end, y_end;

      calculate_vector_coords (m_data->m_V1_layer[time_step_number][i],
                               m_data->m_V2_layer[time_step_number][i],
                               x_begin, y_begin, x_end, y_end,
                               x_vect_l, y_vect_l, x_vect_r, y_vect_r);
      if (fabs (x_begin - x_end) > EPS || fabs (y_begin - y_end) > EPS)
        {
          painter.setPen (QPen (Qt::black, 0.04));
          painter.drawLine (QPointF (x_begin, y_begin), QPointF (x_end, y_end));
          painter.drawLine (QPointF (x_end, y_end),     QPointF (x_vect_l, y_vect_l));
          painter.drawLine (QPointF (x_end, y_end),     QPointF (x_vect_r, y_vect_r));
        }
    }
}

void graph_2d::set_timestep (int timestep)
{
  m_step_number = timestep;
  update ();
}

void graph_2d::run ()
{
//  for (; m_step_number < m_data->m_steps_count - 1; m_step_number++)
//    {
//      sleep  (1);
//      update ();
//    }
//  sleep  (1);
//  update ();
}

void graph_2d::paintEvent (QPaintEvent * /* event */)
{
  QPainter painter (this);
  painter.save ();

  painter.translate (0, height ());
  painter.scale (m_scale_coeff * width () / (m_right_border - m_left_border), -m_scale_coeff * height () / 20);// / (4.0 * (max_y - min_y)));

  painter.setPen (QPen (Qt::red, 0.1));
  painter.drawLine (m_left_border, 0, m_right_border, 0);
  painter.setPen (QPen (Qt::green, 0.1));
  painter.drawLine (0, -10, 0, 10);

  draw_H (m_step_number, painter);
  draw_V (m_step_number, painter);

  painter.restore ();
}
