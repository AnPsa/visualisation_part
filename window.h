#ifndef WINDOW_H
#define WINDOW_H

#include <QGLWidget>
#include <QPoint>

class data_holder;

class graph_2d : public QWidget
{
  Q_OBJECT
  data_holder *data;
  double left_border, right_border;

public:
  graph_2d (QWidget *parent, data_holder *idata);
  ~graph_2d();

  QSize minimumSizeHint () const;
  QSize sizeHint () const;
  void draw_H (int time_step_number, QPainter &painter);
  void H_color (double value, int &red, int &green);
  double scale_coeff;

  //draw

//public slots:
//  void change_func ();
//  void get_closer();
//  void get_further();
//  void double_n();
//  void smaller_n();
//  void delta_function_plus();
//  void delta_function_minus();
//  void delta_function_up();
//  void delta_function_down();
//  void exit_all();

protected:
  void paintEvent (QPaintEvent *event);
};



















//class Scene3D : public QGLWidget
//{
//  GLfloat *VertexArray;
//  GLfloat xRot;
//  GLfloat yRot;
//  GLfloat zRot;
//  GLfloat xTra;
//  GLfloat yTra;
//  GLfloat zTra;
//  GLfloat nSca;

//  QPoint ptrMousePosition;

//  data_holder *data;
//  int draw_status;

//  void scale_plus ();
//  void scale_minus ();
//  void rotate_up  ();
//  void rotate_down ();
//  void rotate_left ();
//  void rotate_right();
//  void translate_down ();
//  void translate_up ();
//  void defaultScene ();
//  void drawAxis ();

//  void H_color (double value);
//  void draw_H  (int time_step_number);
//  void draw_V  (int time_step_number);

//protected:
//  void initializeGL ();
//  void resizeGL (int nWidth, int nHeight);
//  void paintGL ();
//  void mousePressEvent (QMouseEvent* pe);
//  void mouseMoveEvent (QMouseEvent* pe);
//  void mouseReleaseEvent (QMouseEvent*);
//  void wheelEvent (QWheelEvent* pe);
//  void keyPressEvent (QKeyEvent* pe);

//public:
//  Scene3D (QWidget* parent, data_holder *idata);
//  ~Scene3D ();
//};

#endif // WINDOW_H



