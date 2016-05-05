#ifndef WINDOW_H
#define WINDOW_H

#include <QGLWidget>
#include <QPoint>

class data_holder;

class graph_2d : public QWidget
{
  data_holder *m_data;
  double m_left_border, m_right_border;
  double m_scale_coeff;
  int m_step_number;

public:
  graph_2d (QWidget *parent, data_holder *idata);
  ~graph_2d();
  QSize minimumSizeHint () const;
  QSize sizeHint () const;

  void H_color (double value, int &red, int &green);
  void draw_H (int time_step_number, QPainter &painter);
  void draw_V (int time_step_number, QPainter &painter);

  void set_timestep (int timestep);
  void run ();

  void draw_vector_for_v (QPainter &painter, double x_begin, double y_begin, int velocity_counter, int time_step_number);

protected:
  void paintEvent (QPaintEvent *event);
};

#endif // WINDOW_H



