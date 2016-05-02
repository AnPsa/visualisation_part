/// \file inetrface_widget.h

#ifndef INTERFACE_WIDGET_H
#define INTERFACE_WIDGET_H

#include <QWidget>

class graph_2d;
class data_holder;
class QPushButton;
class QSlider;

class interface_widget : public QWidget
{
  Q_OBJECT

  graph_2d    *m_graph_widget;
  QPushButton *m_play_button;
  QSlider     *m_step_slider;

public:
  interface_widget  (QWidget *parent, data_holder *idata);
  ~interface_widget ();

public slots:
  void timestep_changed (int);
  void run_graph ();
};

#endif // INTERFACE_WIDGET_H

