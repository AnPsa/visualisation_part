#ifndef DATA_HOLDER_H
#define DATA_HOLDER_H

#include <vector>
#include <string>

class data_holder
{
public:
  std::vector <std::vector <double> > m_H_layer;
  std::vector <std::vector <double> > m_V1_layer;
  std::vector <std::vector <double> > m_V2_layer;
  std::vector <double> m_x_v;
  std::vector <double> m_y_V;
  std::vector <double> m_x_h;
  std::vector <double> m_y_h;


  int m_dim;
  int m_dim_h;
  int m_steps_count;

  data_holder();

  //in file for H firs to numbers is dim H and stages count
  //in file for V firs numbe is dim
  bool read_data(std::string H_filemane, std::string V_filename);
  bool read_data_for_H(std::string H_filemane);
  bool read_data_for_v(std::string V_filename);
};

#endif // DATA_HOLDER_H
