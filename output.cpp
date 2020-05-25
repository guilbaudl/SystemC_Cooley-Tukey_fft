#include <fstream>
#include <iostream>
#include "output.h"

using std::cout;
using std::cerr;
using std::endl;

void OUTPUT::comportement()
{
  int i = 0;

  std::ofstream fileStream;

  bool is_it_full = false;
  O_data_req = false;

  fileStream.open("output.txt");

  if(!fileStream)
    cerr << "Fichier de sortie non ouvert" << endl;

  wait();

  while(true)
    {
      while (I_data_valid & O_data_req & (i < 8))  // if it is possible to receive data
      {
        out_data[i].real = real_sample_from_fft;
        out_data[i].imag = imag_sample_from_fft;
        i++;

        if (i == 8) // if the buffer is finally full
        {
          is_it_full = true;
          O_data_req = false;
        }
        wait();
      }

      if (is_it_full) // if the buffer is full
      {
        //value = out_data[8-i].real;
        fileStream << out_data[8-i].real << " ";
        //value = out_data[8-i].imag;
        fileStream << out_data[8-i].imag << endl;
        i--;
      }
      
      if (i == 0) // if the buffer is empty
      {
        is_it_full = false;
        O_data_req = true;
      }
      
      wait();
    }
  fileStream.close();
}
