#define SC_INCLUDE_FX
#include <systemc.h>
#include "fft_float.h"
#include "input.h"
#include <fstream>
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

void INPUT::comportement()
{
  std::fstream fileStream("input_samples.txt");

  float value;

  bool is_it_full = false;
  bool flag_eof = false;

  O_data_valid = false;

  if(!fileStream)
    cerr<<"Fichier d'entree non ouvert"<<endl;

  wait();

  while(true)
    {
    if(!fileStream.eof()) // if the file is not empty
    {
      if (!is_it_full) // is_it_full becomes true when out_data reaches the value 8
      {
        fileStream >> value;
        out_data[i].real = (sc_fixed<WL, IWL>)value;
        fileStream >> value;
        out_data[i].imag = (sc_fixed<WL, IWL>)value;
        i++;
      }
    }

    else // if the file is empty
    {
      if (!flag_eof) // just to avoid multiple writing
      {
        cout << "fin du fichier d'entree" << endl;
        flag_eof = true;
      }
    }
      
    if (i == 8) // if the buffer is full
    {
      real_sample_to_fft = out_data[0].real;  // transmit at least one sample before telling
      imag_sample_to_fft = out_data[0].imag;  // to FFT bloc that INPUT is ready to send samples
      i--;

      is_it_full = true; // buffer is full
      O_data_valid = true; // ready to transmit data
    }
    
    while (I_data_req & O_data_valid & (i != 0)) //if it is possible to transmit data
    {
      real_sample_to_fft = out_data[8-i].real;
      imag_sample_to_fft = out_data[8-i].imag;
      i--;
      wait();

      if (i == 0) // if the buffer is empty
      { 
        is_it_full = false;
        O_data_valid = false; 
      }
    }

    wait();
  }
}
