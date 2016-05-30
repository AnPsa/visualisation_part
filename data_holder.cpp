#include "data_holder.h"
#include <stdio.h>
#include <QDebug>

data_holder::data_holder()
{
  min_H = -1;
  max_H = 0;
}

bool data_holder::read_data_for_H(std::string H_filename)
{
  FILE *h_file;
  double temp, tempx, tempy;

  if (!(h_file = fopen (H_filename.c_str (), "r")))
    {
      printf ("Cannot open file %s\n", H_filename.c_str ());
      return false;
    }

  if (fscanf (h_file, "%d%d", &m_dim_h, &m_steps_count) != 2)
    {
      fclose (h_file);
      printf ("HEY1\n");
      return false;
    }

  if (m_dim_h < 1 || m_steps_count < 1)
    {
      fclose (h_file);
      printf ("HEY2\n");
      return false;
    }

  m_H_layer.resize (m_steps_count);
  m_x_h.resize (m_dim_h);
  m_y_h.resize (m_dim_h);

  for (int t = 0; t < m_steps_count; t++)
    {
      m_H_layer[t].resize (m_dim_h);
      for (int i = 0; i < m_dim_h; i++)
        {
          if (fscanf (h_file, "%lf%lf%lf", &temp, &tempx, &tempy) != 3)
            {
              printf ("HEY3\n");
              fclose (h_file);
              return false;
            }

          m_H_layer[t][i] = temp;
          if (min_H > temp || min_H < 0)
            min_H = temp;
          if (max_H < temp)
            max_H = temp;

          m_x_h[i] = tempx;
          m_y_h[i] = tempy;
        }
    }
  m_x_h.push_back (-1);
  m_y_h.push_back (-1);
  fclose (h_file);

  middle_H = (max_H + min_H) / 2.;
  return true;
}


bool data_holder::read_data_for_v (std::string V_filename)
{
  FILE *v_file;
  if (!(v_file = fopen (V_filename.c_str (), "r")))
    {
      printf ("Cannot read file %s\n", V_filename.c_str ());
      return false;
    }

  if (fscanf (v_file, "%d", &m_dim_v) != 1)
    {
      fclose (v_file);
      return false;
    }

  if (m_dim_v < 1 || m_steps_count < 1)
    {
      fclose (v_file);
      return false;
    }

  m_V1_layer.resize (m_steps_count);
  m_V2_layer.resize (m_steps_count);

  m_x_v.resize (m_dim_v);
  m_y_v.resize (m_dim_v);

  for (int t = 0; t < m_steps_count; t++)
    {
      m_V1_layer[t].resize (m_dim_v);
      m_V2_layer[t].resize (m_dim_v);

      for (int i = 0; i < m_dim_v; i++)
        {
          double temp1, temp2, tempx, tempy;
          if (fscanf (v_file, "%lf%lf%lf%lf", &temp1, &temp2, &tempx, &tempy) != 4)
            {
              fclose (v_file);
              return false;
            }

          m_V1_layer[t][i] = temp1;
          m_V2_layer[t][i] = temp2;
          m_x_v[i] = tempx;
          m_y_v[i] = tempy;
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
