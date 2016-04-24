#include "data_holder.h"
#include <stdio.h>



data_holder::data_holder()
{

}
bool data_holder::read_data_for_H(std::string H_filemane)
{
  FILE *h_file = fopen (H_filemane.c_str (), "r");

  if (fscanf (h_file, "%d%d", &m_dim_h, &m_steps_count) != 2)
    return false;

  if (m_dim_h < 1 || m_steps_count < 1)
    return false;


  m_H_layer.resize (m_steps_count);
  for (int t = 0; t < m_steps_count; t++)
    {
      m_H_layer.resize (m_dim_h);
      for (int i = 0; i < m_dim_h; i++)
        {
          double temp;
          if (fscanf (h_file, "%lf", &temp) != 1)
            return false;

          m_H_layer[t][i] = temp;
        }
    }
  fclose (h_file);
  return true;
}


bool data_holder::read_data_for_v (std::string V_filename)
{
  FILE *v_file = fopen (V_filename.c_str (), "r");

  if (fscanf (v_file, "%d", &m_dim) != 1)
    return false;

  if (m_dim < 1 || m_steps_count < 1)
    return false;


  m_V1_layer.resize (m_steps_count);
  m_V2_layer.resize (m_steps_count);

  for (int t = 0; t < m_steps_count; t++)
    {
      m_V1_layer[t].resize (m_dim);
      m_V2_layer[t].resize (m_dim);

      for (int i = 0; i < m_dim; i++)
        {
          double temp1, temp2;
          if (fscanf (v_file, "%lf%lf", &temp1, &temp2) != 2)
            return false;

          m_V1_layer[t][i] = temp1;
          m_V2_layer[t][i] = temp2;
        }
    }
  fclose (v_file);
  return true;
}

bool data_holder::read_data (std::string H_filemane, std::string V_filename)
{
 if (!read_data_for_H (H_filemane))
   {
     printf ("can't read data for H\n");
     return false;
   }

 if (!read_data_for_v (V_filename))
   {
     printf ("can't read data for V\n");
     return false;
   }
 return true;
}


