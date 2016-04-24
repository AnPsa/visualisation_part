#ifndef WINDOW_H
#define WINDOW_H

#include <QGLWidget>
#include <QPoint>

class data_holder;

class Scene3D : public QGLWidget
{
  GLfloat *VertexArray;
  GLfloat xRot;
  GLfloat yRot;
  GLfloat zRot;
  GLfloat zTra;
  GLfloat nSca;

  QPoint ptrMousePosition;

  data_holder *data;

  void scale_plus ();
  void scale_minus ();
  void rotate_up  ();
  void rotate_down ();
  void rotate_left ();
  void rotate_right();
  void translate_down ();
  void translate_up ();
  void defaultScene ();
  void drawAxis ();

  void H_color(double value);
  void draw_H(int time_step_number);

protected:
  void initializeGL ();
  void resizeGL (int nWidth, int nHeight);
  void paintGL ();
  void mousePressEvent (QMouseEvent* pe);
  void mouseMoveEvent (QMouseEvent* pe);
  void mouseReleaseEvent (QMouseEvent*);
  void wheelEvent (QWheelEvent* pe);
  void keyPressEvent (QKeyEvent* pe);

public:
  Scene3D (QWidget* parent, data_holder *idata);
  ~Scene3D ();
};

#endif // WINDOW_H



