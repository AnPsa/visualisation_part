#include "interface_widget.h"
#include "window.h"
#include "data_holder.h"

#include <QLayout>
#include <QPushButton>
#include <QSlider>
#include <QObject>
#include <QDebug>

interface_widget::interface_widget (QWidget *parent, data_holder *idata) : QWidget (parent)
{
  m_graph_widget = new graph_2d (this, idata);

  m_play_button  = new QPushButton ("Play", this);
  m_play_button->setMaximumWidth (100);

  m_step_slider  = new QSlider (Qt::Horizontal, this);
  m_step_slider->setMaximum (idata->m_steps_count - 1);
  QObject::connect (m_step_slider, SIGNAL (valueChanged (int)), this, SLOT (timestep_changed (int)));
  QObject::connect (m_play_button, SIGNAL (pressed ()), this, SLOT (run_graph ()));

  QHBoxLayout *hlayout = new QHBoxLayout (this);
  hlayout->addWidget (m_play_button);
  hlayout->addWidget (m_step_slider);
  QWidget *top_widget = new QWidget (this);
  top_widget->setLayout (hlayout);

  QVBoxLayout *vlayout = new QVBoxLayout ();
  vlayout->addWidget (top_widget);
  vlayout->addWidget (m_graph_widget);

  setLayout (vlayout);
}

interface_widget::~interface_widget ()
{
  delete m_play_button;
  delete m_graph_widget;
}

void interface_widget::timestep_changed (int timestep)
{
  m_graph_widget->set_timestep (timestep);
}

void interface_widget::run_graph ()
{
  m_graph_widget->run ();
}
